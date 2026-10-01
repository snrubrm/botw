#include "Game/AI/Action/actionBackStepToTargetPos.h"

namespace uking::action {

BackStepToTargetPos::BackStepToTargetPos(const InitArg& arg) : BackStepToTarget(arg) {}

BackStepToTargetPos::~BackStepToTargetPos() = default;

bool BackStepToTargetPos::init_(sead::Heap* heap) {
    return BackStepToTarget::init_(heap);
}

void BackStepToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepToTarget::enter_(params);
}

void BackStepToTargetPos::leave_() {
    BackStepToTarget::leave_();
}

void BackStepToTargetPos::loadParams_() {
    BackStepToTarget::loadParams_();
    getStaticParam(&mIsJumpHeightFromHigherPos_s, "IsJumpHeightFromHigherPos");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mPreLandAS_s, "PreLandAS");
    getStaticParam(&mEndAS_s, "EndAS");
}

void BackStepToTargetPos::calc_() {
    BackStepToTarget::calc_();
}

void BackStepToTargetPos::m34() {
    playAS(mStartAS_s.cstr(), false, 0, 0, -1.0f);
}

void BackStepToTargetPos::m35() {
    playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
}

void BackStepToTargetPos::m36() {
    playAS(mPreLandAS_s.cstr(), true, 0, 0, -1.0f);
}

void BackStepToTargetPos::m37() {
    playAS(mEndAS_s.cstr(), true, 0, 0, -1.0f);
}

}  // namespace uking::action
