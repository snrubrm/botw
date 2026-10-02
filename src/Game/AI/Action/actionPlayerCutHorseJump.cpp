#include "Game/AI/Action/actionPlayerCutHorseJump.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutHorseJump::PlayerCutHorseJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutHorseJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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
