#include "Game/AI/Behavior/behaviorFootstepSilencer.h"

namespace uking::behavior {

FootstepSilencer::FootstepSilencer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

FootstepSilencer::~FootstepSilencer() = default;

bool FootstepSilencer::m6(sead::Heap* heap) {
    return true;
}

void FootstepSilencer::m7() {}

void FootstepSilencer::loadParams() {

}

}  // namespace uking::behavior
