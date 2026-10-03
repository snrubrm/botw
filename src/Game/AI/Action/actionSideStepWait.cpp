#include "Game/AI/Action/actionSideStepWait.h"

namespace uking::action {

SideStepWait::SideStepWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStepWait::~SideStepWait() = default;

void SideStepWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SideStepWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void SideStepWait::loadParams_() {
    getStaticParam(&mParams.mFirstStepDist_s, "FirstStepDist");
    getStaticParam(&mParams.mSecondStepDist_s, "SecondStepDist");
    getStaticParam(&mParams.mThirdStepDist_s, "ThirdStepDist");
    getStaticParam(&mParams.mFourthStepDist_s, "FourthStepDist");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mFirstStepHeight_s, "FirstStepHeight");
    getStaticParam(&mParams.mSecondStepHeight_s, "SecondStepHeight");
    getStaticParam(&mParams.mThirdStepHeight_s, "ThirdStepHeight");
    getStaticParam(&mParams.mFourthStepHeight_s, "FourthStepHeight");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
}

void SideStepWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
