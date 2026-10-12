#include "Game/AI/Action/actionWarpPlayerToAnchor.h"

namespace uking::action {

WarpPlayerToAnchor::WarpPlayerToAnchor(const InitArg& arg) : DestPlayerWarpBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WarpPlayerToAnchor::~WarpPlayerToAnchor() {
    ;
}

bool WarpPlayerToAnchor::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayerToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayerToAnchor::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayerToAnchor::loadParams_() {
    DestPlayerWarpBase::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void WarpPlayerToAnchor::calc_() {
    DestPlayerWarpBase::calc_();
}

bool WarpPlayerToAnchor::m33() {
    return true;
}

}  // namespace uking::action
