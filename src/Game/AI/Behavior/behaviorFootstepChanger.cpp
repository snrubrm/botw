#include "Game/AI/Behavior/behaviorFootstepChanger.h"

namespace uking::behavior {

FootstepChanger::FootstepChanger(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
FootstepChanger::~FootstepChanger() {
    ;
}

bool FootstepChanger::m6(sead::Heap* heap) {
    return true;
}

void FootstepChanger::m7() {}

void FootstepChanger::loadParams() {
    getStaticParam(&mChangeDuration_s, "ChangeDuration");
    getStaticParam(&mFootstepKey_s, "FootstepKey");
}

}  // namespace uking::behavior
