#include "Game/AI/AI/aiTargetTypeSelector.h"

namespace uking::ai {

TargetTypeSelector::TargetTypeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetTypeSelector::~TargetTypeSelector() = default;

bool TargetTypeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetTypeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetTypeSelector::leave_() {
    *mIsTrgTargetChangeToPlayer_a = false;
}

void TargetTypeSelector::loadParams_() {
    getAITreeVariable(&mIsTrgTargetChangeToPlayer_a, "IsTrgTargetChangeToPlayer");
}

bool TargetTypeSelector::isFailed() const {
    if (getCurrentChild())
        return getCurrentChild()->isFailed();
    return true;
}

bool TargetTypeSelector::isFinished() const {
    if (getCurrentChild())
        return getCurrentChild()->isFinished();
    return true;
}

bool TargetTypeSelector::isChangeable() const {
    if (getCurrentChild())
        return getCurrentChild()->isChangeable();
    return true;
}

}  // namespace uking::ai
