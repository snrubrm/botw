#include "Game/AI/Action/actionSlippedWalk.h"

namespace uking::action {

SlippedWalk::SlippedWalk(const InitArg& arg) : SlippedWalkBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SlippedWalk::~SlippedWalk() {
    ;
}

bool SlippedWalk::init_(sead::Heap* heap) {
    return SlippedWalkBase::init_(heap);
}

void SlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedWalkBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SlippedWalk::leave_() {
    SlippedWalkBase::leave_();
}

void SlippedWalk::loadParams_() {
    SlippedWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedWalk::calc_() {
    SlippedWalkBase::calc_();
}

}  // namespace uking::action
