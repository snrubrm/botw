#include "Game/AI/Action/actionJumpTackle.h"

namespace uking::action {

// NON_MATCHING: store scheduling (param zeroing is sunk below the vtable store)
JumpTackle::JumpTackle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpTackle::~JumpTackle() = default;

bool JumpTackle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpTackle::leave_() {
    m33();
    sub_71005DA114(mActor, &_50);
}

void JumpTackle::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMinSpeed_s, "MinSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightMaxOffset_s, "JumpHeightMaxOffset");
    getStaticParam(&mIsFinishedAtPreLandFrame_s, "IsFinishedAtPreLandFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void JumpTackle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
