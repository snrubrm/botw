#include "Game/AI/Behavior/behaviorSetForceSmallRagdoll.h"

namespace uking::behavior {

SetForceSmallRagdoll::SetForceSmallRagdoll(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetForceSmallRagdoll::~SetForceSmallRagdoll() = default;

bool SetForceSmallRagdoll::m6(sead::Heap* heap) {
    return true;
}

void SetForceSmallRagdoll::m7() {}

void SetForceSmallRagdoll::loadParams() {

}

}  // namespace uking::behavior
