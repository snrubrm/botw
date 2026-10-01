#include "Game/AI/AI/aiHorsePrevRiddenStatusSelector.h"

namespace uking::ai {

HorsePrevRiddenStatusSelector::HorsePrevRiddenStatusSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorsePrevRiddenStatusSelector::~HorsePrevRiddenStatusSelector() = default;

bool HorsePrevRiddenStatusSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorsePrevRiddenStatusSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710043C1D4(params);
}

void HorsePrevRiddenStatusSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorsePrevRiddenStatusSelector::loadParams_() {}

void HorsePrevRiddenStatusSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable())
        sub_710043C1D4(nullptr);
}

}  // namespace uking::ai
