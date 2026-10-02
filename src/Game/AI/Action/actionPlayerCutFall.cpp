#include "Game/AI/Action/actionPlayerCutFall.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayerCutFall::PlayerCutFall(const InitArg& arg) : PlayerAction(arg) {}

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
    PlayerAction::leave_();
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
