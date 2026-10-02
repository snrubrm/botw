#include "Game/AI/Behavior/behaviorSetCollisionImpulseScale.h"

namespace uking::behavior {

SetCollisionImpulseScale::SetCollisionImpulseScale(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetCollisionImpulseScale::~SetCollisionImpulseScale() = default;

bool SetCollisionImpulseScale::m6(sead::Heap* heap) {
    return true;
}

void SetCollisionImpulseScale::m7() {}

void SetCollisionImpulseScale::loadParams() {
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::behavior
