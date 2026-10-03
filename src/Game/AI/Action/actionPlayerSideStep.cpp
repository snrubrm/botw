#include "Game/AI/Action/actionPlayerSideStep.h"
#include <cstring>

namespace uking::action {

PlayerSideStep::PlayerSideStep(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mSpeedF_s, 0, 0x48);
}

void PlayerSideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSideStep::leave_() {
    PlayerAction::leave_();
}

void PlayerSideStep::loadParams_() {
    getStaticParam(&mSpeedF_s, "SpeedF");
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mFSpeedF_s, "FSpeedF");
    getStaticParam(&mFHeight_s, "FHeight");
    getStaticParam(&mUHeight_s, "UHeight");
    getStaticParam(&mNoDamageTime_s, "NoDamageTime");
    getStaticParam(&mJustAvoidTime_s, "JustAvoidTime");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
    getStaticParam(&mMySlowStartFrame_s, "MySlowStartFrame");
}

void PlayerSideStep::calc_() {
    PlayerAction::calc_();
}

bool PlayerSideStep::isChangeable() const {
    return true;
}

}  // namespace uking::action
