#include "Game/AI/Behavior/behaviorSetRagdollBodyForceKeyframed.h"

namespace uking::behavior {

SetRagdollBodyForceKeyframed::SetRagdollBodyForceKeyframed(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetRagdollBodyForceKeyframed::~SetRagdollBodyForceKeyframed() {
    ;
}

bool SetRagdollBodyForceKeyframed::m6(sead::Heap* heap) {
    return true;
}

void SetRagdollBodyForceKeyframed::m7() {}

}  // namespace uking::behavior
