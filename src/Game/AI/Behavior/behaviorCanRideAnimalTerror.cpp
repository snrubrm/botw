#include "Game/AI/Behavior/behaviorCanRideAnimalTerror.h"

namespace uking::behavior {

CanRideAnimalTerror::CanRideAnimalTerror(const InitArg& arg) : TerrorBehavior(arg) {}

CanRideAnimalTerror::~CanRideAnimalTerror() = default;

bool CanRideAnimalTerror::m6(sead::Heap* heap) {
    return TerrorBehavior::m6(heap);
}

void CanRideAnimalTerror::m9() {
    TerrorBehavior::m9();
}

void CanRideAnimalTerror::loadParams() {
    TerrorBehavior::loadParams();
    getStaticParam(&mLevelForRiddenPlayer_s, "LevelForRiddenPlayer");
}

}  // namespace uking::behavior
