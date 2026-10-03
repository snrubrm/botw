#include "Game/AI/Action/actionPlayerCutFall.h"
#include <cstring>
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

// The parameter pointers are cleared with an explicit memset in the constructor body (the original
// tail-calls memset, which only a call from the source produces).
PlayerCutFall::PlayerCutFall(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mParashawlInvalidTime_s, 0, 0x50);
}

void PlayerCutFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(26);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(29);
    static_cast<ksys::act::Player*>(mActor)->_cf8.setBit(2);
    static_cast<ksys::act::Player*>(mActor)->_cf8.setBit(0);

    if (static_cast<ksys::act::Player*>(mActor)->_1cb0 == 0x54)
        ui::sub_7100A95F5C(0x54);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 != player->getEquipmentTypeName(1))
        static_cast<ksys::act::Player*>(mActor)->x_38(1);

    player = static_cast<ksys::act::Player*>(mActor);
    const int weapon_idx = player->playerWeapons_return0();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(
            player->getWeapons()->getEquippedWeapon(weapon_idx))) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
    }

    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutFall", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mParashawlInvalidTime_s, *mParashawlInvalidTime_s);
}

void PlayerCutFall::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = 0;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100888294()) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(1)) {
            if (static_cast<ksys::act::Player*>(mActor)->_d24 == 0)
                static_cast<ksys::act::Player*>(mActor)->x_7();
        }
    }
}

void PlayerCutFall::loadParams_() {
    getStaticParam(&mParashawlInvalidTime_s, "ParashawlInvalidTime");
    getStaticParam(&mFallSpAttackHeight_s, "FallSpAttackHeight");
    getStaticParam(&mFallSpAttackRadiusMin_s, "FallSpAttackRadiusMin");
    getStaticParam(&mFallSpAttackRadiusMax_s, "FallSpAttackRadiusMax");
    getStaticParam(&mFallSpAttackRadiusAdd_s, "FallSpAttackRadiusAdd");
    getStaticParam(&mFallSpAttackRadiusAddLSword_s, "FallSpAttackRadiusAddLSword");
    getStaticParam(&mFallSpLargeAttackRadius_s, "FallSpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
}

void PlayerCutFall::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutFall::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
