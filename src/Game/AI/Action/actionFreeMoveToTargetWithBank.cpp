#include "Game/AI/Action/actionFreeMoveToTargetWithBank.h"

namespace uking::action {

FreeMoveToTargetWithBank::FreeMoveToTargetWithBank(const InitArg& arg) : FreeMoveToTarget(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
FreeMoveToTargetWithBank::~FreeMoveToTargetWithBank() {
    ;
}

bool FreeMoveToTargetWithBank::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToTargetWithBank::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
    _e0.value = 0;
    _e0.prev_value = 0;
    _ec = 0;
}

void FreeMoveToTargetWithBank::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToTargetWithBank::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mBankAngleMax_s, "BankAngleMax");
    getStaticParam(&mLimitMoveAngle4Bank_s, "LimitMoveAngle4Bank");
}

void FreeMoveToTargetWithBank::calc_() {
    FreeMoveToTarget::calc_();
}

}  // namespace uking::action
