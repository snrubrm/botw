#include "Game/AI/Action/actionJumpToTarget.h"

namespace uking::action {

JumpToTarget::JumpToTarget(const InitArg& arg) : JumpTo(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
JumpToTarget::~JumpToTarget() {
    ;
}

bool JumpToTarget::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void JumpToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTo::enter_(params);
}

void JumpToTarget::leave_() {
    JumpTo::leave_();
}

void JumpToTarget::loadParams_() {
    JumpTo::loadParams_();
    getStaticParam(&mPreJumpAS_s, "PreJumpAS");
    getStaticParam(&mJumpAS_s, "JumpAS");
    getStaticParam(&mLandAS_s, "LandAS");
}

void JumpToTarget::calc_() {
    JumpTo::calc_();
}

void JumpToTarget::m32() {
    playAS(mPreJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTarget::m33() {
    playAS(mJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTarget::m34() {
    playAS(mLandAS_s.cstr(), false, 0, 0, -1.0f);
}

bool JumpToTarget::m35() {
    return !mPreJumpAS_s.isEmpty();
}

bool JumpToTarget::m36() {
    return !mJumpAS_s.isEmpty();
}

bool JumpToTarget::m37() {
    return !mLandAS_s.isEmpty();
}

}  // namespace uking::action
