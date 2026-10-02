#include "Game/AI/Behavior/behaviorGiantDownReaction.h"

namespace uking::behavior {

GiantDownReaction::GiantDownReaction(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GiantDownReaction::~GiantDownReaction() {
    ;
}

bool GiantDownReaction::m6(sead::Heap* heap) {
    return true;
}

void GiantDownReaction::m8() {
    _70 = false;
    _74 = -1.0f;
}

void GiantDownReaction::m9() {}

}  // namespace uking::behavior
