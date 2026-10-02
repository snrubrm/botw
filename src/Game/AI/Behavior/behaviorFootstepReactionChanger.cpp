#include "Game/AI/Behavior/behaviorFootstepReactionChanger.h"

namespace uking::behavior {

FootstepReactionChanger::FootstepReactionChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
FootstepReactionChanger::~FootstepReactionChanger() {
    ;
}

bool FootstepReactionChanger::m6(sead::Heap* heap) {
    return true;
}

void FootstepReactionChanger::m7() {}

}  // namespace uking::behavior
