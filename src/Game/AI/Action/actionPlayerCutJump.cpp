#include "Game/AI/Action/actionPlayerCutJump.h"
#include <cstring>
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutJump::PlayerCutJump(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mAttackRatioNSword_s, 0, 0xa8);
}

void PlayerCutJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutJump::loadParams_() {
    getStaticParam(&mAttackRatioNSword_s, "AttackRatioNSword");
    getStaticParam(&mAttackRatioLSword_s, "AttackRatioLSword");
    getStaticParam(&mAttackRatioSpear_s, "AttackRatioSpear");
    getStaticParam(&mCutJumpSpeedF_s, "CutJumpSpeedF");
    getStaticParam(&mCutJumpHeight_s, "CutJumpHeight");
    getStaticParam(&mCutJumpShortSpeedF_s, "CutJumpShortSpeedF");
    getStaticParam(&mCutJumpShortHeight_s, "CutJumpShortHeight");
    getStaticParam(&mCutJumpSpeedFLSword_s, "CutJumpSpeedFLSword");
    getStaticParam(&mAimDistOffset_s, "AimDistOffset");
    getStaticParam(&mSwingFrameBeforeGround_s, "SwingFrameBeforeGround");
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

void PlayerCutJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutJump::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
