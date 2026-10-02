#include "Game/AI/Action/actionWarpPlayerToAnchor.h"

namespace uking::action {

WarpPlayerToAnchor::WarpPlayerToAnchor(const InitArg& arg) : WarpPlayerBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WarpPlayerToAnchor::~WarpPlayerToAnchor() {
    ;
}

bool WarpPlayerToAnchor::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayerToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayerToAnchor::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayerToAnchor::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void WarpPlayerToAnchor::calc_() {
    WarpPlayerBase::calc_();
}

bool WarpPlayerToAnchor::m33() {
    return true;
}

}  // namespace uking::action
