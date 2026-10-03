#include "Game/AI/Action/actionForkJumpToTargetOnDownEnd.h"

namespace uking::action {

ForkJumpToTargetOnDownEnd::ForkJumpToTargetOnDownEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkJumpToTargetOnDownEnd::~ForkJumpToTargetOnDownEnd() = default;

bool ForkJumpToTargetOnDownEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkJumpToTargetOnDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkJumpToTargetOnDownEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkJumpToTargetOnDownEnd::loadParams_() {
    getStaticParam(&mParams.mAngleDir_s, "AngleDir");
    getStaticParam(&mParams.mJumpDist_s, "JumpDist");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mLimitSpeed_s, "LimitSpeed");
    getStaticParam(&mParams.mEndGrSpeed_s, "EndGrSpeed");
    getStaticParam(&mParams.mJumpMinDist_s, "JumpMinDist");
    getStaticParam(&mParams.mOnGround_s, "OnGround");
    getStaticParam(&mParams.mIsBasisByTarget_s, "IsBasisByTarget");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void ForkJumpToTargetOnDownEnd::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
