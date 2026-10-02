#include "Game/AI/Behavior/behaviorAnimalCounterFlagOn.h"

namespace uking::behavior {

AnimalCounterFlagOn::AnimalCounterFlagOn(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalCounterFlagOn::~AnimalCounterFlagOn() = default;

bool AnimalCounterFlagOn::m6(sead::Heap* heap) {
    return true;
}

void AnimalCounterFlagOn::m7() {}

void AnimalCounterFlagOn::loadParams() {
    getAITreeVariable(&mAnimalEnableCounterFlag_a, "AnimalEnableCounterFlag");
}

}  // namespace uking::behavior
