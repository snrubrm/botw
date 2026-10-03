#include "Game/AI/Action/actionPlayerCutHorseJump.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayerCutHorseJump::PlayerCutHorseJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutHorseJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(26);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cf8.setBit(2);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 != player->getEquipmentTypeName(1))
        static_cast<ksys::act::Player*>(mActor)->x_38(1);

    player = static_cast<ksys::act::Player*>(mActor);
    const int weapon_idx = player->playerWeapons_return0();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(
            player->getWeapons()->getEquippedWeapon(weapon_idx))) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
    }

    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutJumpHorseRide", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_1834 = static_cast<ksys::act::Player*>(mActor)->x_5();
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68.value = player->_1834.value;
    static_cast<ksys::act::Player*>(mActor)->_1cbf = 0;
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mParashawlInvalidTime_s, *mParashawlInvalidTime_s);
}

void PlayerCutHorseJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutHorseJump::loadParams_() {
    getStaticParam(&mAttackRate_s, "AttackRate");
    getStaticParam(&mFallSpAttackHeight_s, "FallSpAttackHeight");
    getStaticParam(&mFallSpAttackRadiusMin_s, "FallSpAttackRadiusMin");
    getStaticParam(&mFallSpAttackRadiusMax_s, "FallSpAttackRadiusMax");
    getStaticParam(&mFallSpAttackRadiusAdd_s, "FallSpAttackRadiusAdd");
    getStaticParam(&mFallSpAttackRadiusAddLSword_s, "FallSpAttackRadiusAddLSword");
    getStaticParam(&mFallSpAttackCheckUnderDist_s, "FallSpAttackCheckUnderDist");
    getStaticParam(&mFallSpLargeAttackRadius_s, "FallSpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
    getStaticParam(&mParashawlInvalidTime_s, "ParashawlInvalidTime");
}

void PlayerCutHorseJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutHorseJump::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
