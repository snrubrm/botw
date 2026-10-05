#include "Game/AI/Action/actionSwimTurnBase.h"

namespace uking::action {

SwimTurnBase::SwimTurnBase(const InitArg& arg) : SwimRotateBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwimTurnBase::~SwimTurnBase() {
    ;
}

bool SwimTurnBase::init_(sead::Heap* heap) {
    return SwimRotateBase::init_(heap);
}

void SwimTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimRotateBase::enter_(params);
}

void SwimTurnBase::leave_() {
    SwimRotateBase::leave_();
}

void SwimTurnBase::loadParams_() {
    SwimRotateBase::loadParams_();
    getStaticParam(&mFinRotate_s, "FinRotate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SwimTurnBase::calc_() {
    SwimRotateBase::calc_();
}

// NON_MATCHING: the vector assignment naturally emits three scalar copies.
void SwimTurnBase::m32(sead::Vector3f* out) {
    if (out)
        *out = *mTargetPos_d;
}

}  // namespace uking::action
