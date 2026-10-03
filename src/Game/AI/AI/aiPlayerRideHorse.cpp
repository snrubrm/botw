#include "Game/AI/AI/aiPlayerRideHorse.h"

namespace uking::ai {

PlayerRideHorse::PlayerRideHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _ac.rate = -1.0f;
}

PlayerRideHorse::~PlayerRideHorse() = default;

bool PlayerRideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerRideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerRideHorse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerRideHorse::loadParams_() {
    getStaticParam(&mParams.mDoForbidTime_s, "DoForbidTime");
    getStaticParam(&mParams.mThrowPowerY_s, "ThrowPowerY");
    getStaticParam(&mParams.mThrowPowerF_s, "ThrowPowerF");
    getStaticParam(&mParams.mBackDismountSpeed_s, "BackDismountSpeed");
    getStaticParam(&mParams.mWaistAngleApplyRateFoward_s, "WaistAngleApplyRateFoward");
    getStaticParam(&mParams.mWaistAngleApplyRateBack_s, "WaistAngleApplyRateBack");
    getStaticParam(&mParams.mMoveNoise_s, "MoveNoise");
    getStaticParam(&mParams.mSwordAttackNoise_s, "SwordAttackNoise");
    getStaticParam(&mParams.mAimAngleAddApplyAngle_s, "AimAngleAddApplyAngle");
    getStaticParam(&mParams.mAimAngleAdd_s, "AimAngleAdd");
    getStaticParam(&mParams.mAimAngleAddApplySpeed_s, "AimAngleAddApplySpeed");
    getStaticParam(&mParams.mLowerAngleWaitTime_s, "LowerAngleWaitTime");
    getDynamicParam(&mParams.mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
    getStaticParam(&mParams.mLynelRodeoCutNum_s, "LynelRodeoCutNum");
}

}  // namespace uking::ai
