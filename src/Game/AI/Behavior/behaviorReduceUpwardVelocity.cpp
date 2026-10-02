#include "Game/AI/Behavior/behaviorReduceUpwardVelocity.h"

namespace uking::behavior {

ReduceUpwardVelocity::ReduceUpwardVelocity(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ReduceUpwardVelocity::~ReduceUpwardVelocity() = default;

bool ReduceUpwardVelocity::m6(sead::Heap* heap) {
    return true;
}

void ReduceUpwardVelocity::m8() {}

void ReduceUpwardVelocity::m9() {}

void ReduceUpwardVelocity::loadParams() {
    getStaticParam(&mImpulseScale_s, "ImpulseScale");
    getStaticParam(&mMinDownImpulse_s, "MinDownImpulse");
}

}  // namespace uking::behavior
