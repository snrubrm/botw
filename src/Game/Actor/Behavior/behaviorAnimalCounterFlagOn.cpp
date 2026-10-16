#include "Game/Actor/Behavior/behaviorAnimalCounterFlagOn.h"

namespace uking::behavior {

AnimalCounterFlagOn::AnimalCounterFlagOn(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalCounterFlagOn::~AnimalCounterFlagOn() = default;

bool AnimalCounterFlagOn::init_(sead::Heap* heap) {
    return true;
}

void AnimalCounterFlagOn::calc() {}

void AnimalCounterFlagOn::loadParams() {
    getAITreeVariable(&mAnimalEnableCounterFlag_a, "AnimalEnableCounterFlag");
}

void AnimalCounterFlagOn::enter() {
    if (mAnimalEnableCounterFlag_a)
        *mAnimalEnableCounterFlag_a = true;
}

void AnimalCounterFlagOn::leave() {
    if (mAnimalEnableCounterFlag_a)
        *mAnimalEnableCounterFlag_a = false;
}

}  // namespace uking::behavior
