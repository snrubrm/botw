#include "Game/Actor/Player/Action/actionPlayerAtnMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerAtnMove::PlayerAtnMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool a = static_cast<ksys::act::Player*>(mActor)->m188();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    auto& chase_speed = player->_20bc;
    const f32 limit = player->sub_71008901D0();
    chase_speed.setToMin(limit);
    if (!a) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_1dd0.value < 2.0f)
            p->_1dd0 = ksys::Timer(2.0f, 2.0f, -1.0f);
    }
    static_cast<ksys::act::Player*>(mActor)->_1810 = sead::Vector3f(0.0f, 1.0f, 0.0f);
    auto* p2 = static_cast<ksys::act::Player*>(mActor);
    if (p2->_c50.isOnBit(34)) {
        p2->_1e6c.value = 15.0f;
        p2->_1e6c.previous_value = 15.0f;
    }
}

void PlayerAtnMove::leave_() {
    if (mActor->getASList()->x_1(1, 1) == "MoveAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (mActor->getASList()->x_1(1, 1) == "MoveUnsteadyUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerAtnMove::loadParams_() {}

// NON_MATCHING: the original addresses mActor through `this` (ours through &mActor) and orders the two angle
// arguments differently on the stack.
void PlayerAtnMove::calc_() {
    if (!(static_cast<ksys::act::Player*>(mActor)->_1e6c.value <= sead::Mathf::epsilon())) {
        static_cast<ksys::act::Player*>(mActor)->_1e6c.update();
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if ((player->m359() || !player->m179() || player->_c40.isOnBit(30)) &&
            !ksys::act::playerIsReloadingOrChargingOrShootingBow(
                static_cast<ksys::act::Player*>(mActor))) {
            auto* p = static_cast<ksys::act::Player*>(mActor);
            if ((!p->_c44.isOnBit(8) || p->_d11) &&
                !(p->runeMgrCheckCanUseCryonis() && p->sub_71008494B8()) &&
                !static_cast<ksys::act::Player*>(mActor)->sub_7100888618() &&
                !static_cast<ksys::act::Player*>(mActor)->_d10) {
                static_cast<ksys::act::Player*>(mActor)->sub_7100857390();
            }
        }
    }

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_209c > 0.05f &&
        !player->sub_7100869814(
            ksys::util::angleDiff(player->_1c74, player->x_5()),
            ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & 0x20000000))) {
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x400);
    } else {
        static_cast<ksys::act::Player*>(mActor)->_cf0.reset(0x400);
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(3))
            static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
    }
    {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(6))
            static_cast<ksys::act::Player*>(mActor)->x_36();
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008911F0();
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        static_cast<ksys::act::Player*>(mActor)->sub_7100877E2C();
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f pos;
        if (controller->sub_7100F5F234(&pos))
            static_cast<ksys::act::Player*>(mActor)->_1810 = pos;
        static_cast<ksys::act::Player*>(mActor)->sub_7100881DFC(
            static_cast<ksys::act::Player*>(mActor)->_1810.y, false);
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerAtnMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
