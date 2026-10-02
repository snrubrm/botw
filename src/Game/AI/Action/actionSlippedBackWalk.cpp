#include "Game/AI/Action/actionSlippedBackWalk.h"

namespace uking::action {

SlippedBackWalk::SlippedBackWalk(const InitArg& arg) : SlippedBackWalkBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SlippedBackWalk::~SlippedBackWalk() {
    ;
}

bool SlippedBackWalk::init_(sead::Heap* heap) {
    return SlippedBackWalkBase::init_(heap);
}

void SlippedBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedBackWalkBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SlippedBackWalk::leave_() {
    SlippedBackWalkBase::leave_();
}

void SlippedBackWalk::loadParams_() {
    SlippedBackWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedBackWalk::calc_() {
    SlippedBackWalkBase::calc_();
}

}  // namespace uking::action
