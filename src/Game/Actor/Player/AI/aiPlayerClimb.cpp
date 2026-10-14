#include "Game/Actor/Player/AI/aiPlayerClimb.h"
#include "Game/gameUnk_710246d058.h"
#include "Game/UI/uiUtils.h"
#include "Game/Actor/aiUnk_710073BB28.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerClimb::PlayerClimb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerClimb::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the two animation-value stores reload the actor separately.
void PlayerClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    using Player = ksys::act::Player;
    static_cast<Player*>(mActor)->_c40.reset(2);
    static_cast<Player*>(mActor)->_c40.reset(0x400000);
    static_cast<Player*>(mActor)->x_8(false, false);
    static_cast<Player*>(mActor)->_20bc.value = 0.0f;
    static_cast<Player*>(mActor)->_20bc.prev_value = 0.0f;
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx, nullptr);
    else
        sub_7100829AA0();
}

void PlayerClimb::leave_() {
    using Player = ksys::act::Player;
    static_cast<Player*>(mActor)->_c40.reset(2);
    static_cast<Player*>(mActor)->_2158 = static_cast<Player*>(mActor)->_1770.y;
    if (static_cast<Player*>(mActor)->_20bc.value == 0.0f)
        static_cast<Player*>(mActor)->_1c68 = static_cast<Player*>(mActor)->x_5();
    static_cast<Player*>(mActor)->_1dd0 = ksys::Timer(*mNoClimbTime_s, *mNoClimbTime_s);
    if (static_cast<Player*>(mActor)->_c48.isOnBit(19))
        static_cast<Player*>(mActor)->switchToAnimSequenceMaybe("Fall", true, -1.0f);
}

bool PlayerClimb::sub_7100829F70() {
    using Player = ksys::act::Player;
    static_cast<Player*>(mActor)->sub_710086B834();
    if (static_cast<Player*>(mActor)->_1cb0 == -1)
        return false;
    if (!static_cast<Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(0))
        return false;
    ui::sub_7100A95F5C(static_cast<Player*>(mActor)->_1cb0);
    const s32 type = static_cast<Player*>(mActor)->_1cb0;
    switch (type) {
    case 22:
    case 23:
    case 24:
    case 25:
        static_cast<Player*>(mActor)->sub_710086BCF8();
        return true;
    case 26:
    case 27: {
        ksys::act::BaseProcLink link;
        ksys::act::Attention::instance()->sub_7100D747D8(&link);
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        ui::showCannotPickupBuyAnyMoreMessageMaybe(accessor.getName(), false);
        sub_710073BADC();
        break;
    }
    default:
        break;
    }
    return false;
}

void PlayerClimb::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
}

bool PlayerClimb::isFailed() const {
    if (getCurrentChild()->isFailed()) {
        if (isCurrentChild("壁登り"))
            return true;
    }
    return false;
}

bool PlayerClimb::isFinished() const {
    if (getCurrentChild()->isFinished()) {
        if (isCurrentChild("壁登り"))
            return true;
    }
    return false;
}

// NON_MATCHING: string and angle temporaries use different stack slots and store ordering.
void PlayerClimb::calc_() {
    using Player = ksys::act::Player;
    sub_7100829E68();
    if (handlePendingChildChange())
        return;
    sub_7100829F70();
    if (isCurrentChild("壁登り")) {
        if (sub_710082A058())
            return;
        if (static_cast<Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(32))
            static_cast<Player*>(mActor)->sub_71008921A8();
    }
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("武器ペグ")) {
        sub_7100829AA0();
        return;
    }
    if (static_cast<Player*>(mActor)->get17d0()->playerCheckController(2)) {
        auto* player = static_cast<Player*>(mActor);
        if (player->_209c > 0.05f &&
            player->sub_7100869814(
                ksys::util::angleDiff(player->_1c74, player->x_5()),
                ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & 0x20000000)) == 1) {
            static_cast<Player*>(mActor)->_c44.set(0x2000000);
            return;
        }
    }
    static_cast<Player*>(mActor)->_c44.reset(0x2000000);
}

void PlayerClimb::sub_7100829AA0() {
    using Player = ksys::act::Player;
    ksys::act::ai::InlineParamPack pack;
    if (static_cast<Player*>(mActor)->_cec.isOnBit(7) || static_cast<Player*>(mActor)->_cf4.isOnBit(19) ||
        mActor->getVelocity().y > -0.2f) {
        pack.addBool(false, "EnableStartAnm", -1);
    } else {
        pack.addBool(true, "EnableStartAnm", -1);
    }
    if (static_cast<Player*>(mActor)->m194())
        pack.addBool(true, "FromParashawl", -1);
    else
        pack.addBool(false, "FromParashawl", -1);
    pack.addBool(static_cast<Player*>(mActor)->_1cbc == 10, "EnableClimbDown", -1);
    changeChild("壁登り", &pack);
    auto* player = static_cast<Player*>(mActor);
    player->_cec.makeAllZero();
    player->_cf0.makeAllZero();
    player->_cf4.makeAllZero();
    player->_cf8.makeAllZero();
    static_cast<Player*>(mActor)->_cec.set(0x80);
    static_cast<Player*>(mActor)->_cec.set(0x10);
    static_cast<Player*>(mActor)->_cf0.set(0x200);
    static_cast<Player*>(mActor)->_cf4.set(0x10);
    static_cast<Player*>(mActor)->_cf4.set(0x80);
}

// NON_MATCHING: register choice / order of the last `to` component
void PlayerClimb::sub_7100829E68() {
    auto* xlink = mActor->getXLink();
    if (!xlink)
        return;
    auto* user = xlink->_50;
    if (!user)
        return;

    ksys::phys::MaterialMask mask;
    const auto& mtx = mActor->getMtx();
    const sead::Vector3f dir = mtx.getBase(2);
    const sead::Vector3f from = mtx.getTranslation();
    const sead::Vector3f to = dir * 1.5f + from;
    if (sub_710072E928(from, to, nullptr, nullptr, &mask, 0.0f)) {
        const int material = mask.getMaterial();
        user->setPropertyValue(0, material);
        const int sub_material = mask.getSubMaterialIdx();
        user->setPropertyValue(1, ksys::xlink::Manager::instance()->getSubMaterialIndex(material, sub_material));
    }
}

}  // namespace uking::ai
