#include "Game/AI/Behavior/behaviorForceFixed.h"

namespace uking::behavior {

ForceFixed::ForceFixed(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceFixed::~ForceFixed() = default;

bool ForceFixed::m6(sead::Heap* heap) {
    return true;
}

void ForceFixed::loadParams() {

}

}  // namespace uking::behavior
