#include "Game/AI/Behavior/behaviorForceFallCliffEdgeChanger.h"

namespace uking::behavior {

ForceFallCliffEdgeChanger::ForceFallCliffEdgeChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ForceFallCliffEdgeChanger::~ForceFallCliffEdgeChanger() = default;

bool ForceFallCliffEdgeChanger::m6(sead::Heap* heap) {
    return true;
}

void ForceFallCliffEdgeChanger::m7() {}

void ForceFallCliffEdgeChanger::loadParams() {
    getStaticParam(&mState_s, "State");
}

}  // namespace uking::behavior
