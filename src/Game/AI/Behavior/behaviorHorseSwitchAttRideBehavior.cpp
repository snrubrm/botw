#include "Game/AI/Behavior/behaviorHorseSwitchAttRideBehavior.h"

namespace uking::behavior {

HorseSwitchAttRideBehavior::HorseSwitchAttRideBehavior(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

HorseSwitchAttRideBehavior::~HorseSwitchAttRideBehavior() = default;

bool HorseSwitchAttRideBehavior::m6(sead::Heap* heap) {
    return true;
}

void HorseSwitchAttRideBehavior::m7() {}

void HorseSwitchAttRideBehavior::loadParams() {

}

}  // namespace uking::behavior
