#include "Game/AI/Behavior/behaviorPlayerSlipXLinkEventBehavior.h"

namespace uking::behavior {

// NON_MATCHING: the original stores _48 after _50 (field types not known yet)
PlayerSlipXLinkEventBehavior::PlayerSlipXLinkEventBehavior(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

PlayerSlipXLinkEventBehavior::~PlayerSlipXLinkEventBehavior() = default;

bool PlayerSlipXLinkEventBehavior::m6(sead::Heap* heap) {
    return true;
}

void PlayerSlipXLinkEventBehavior::loadParams() {

}

}  // namespace uking::behavior
