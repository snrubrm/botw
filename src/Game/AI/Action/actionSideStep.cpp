#include "Game/AI/Action/actionSideStep.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
SideStep::SideStep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStep::~SideStep() = default;

void SideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SideStep::leave_() {
    ksys::act::ai::Action::leave_();
}

void SideStep::loadParams_() {
    getStaticParam(&mParams.mRotSpeedRatio_s, "RotSpeedRatio");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void SideStep::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SideStep::isChangeable() const {
    return false;
}

}  // namespace uking::action
