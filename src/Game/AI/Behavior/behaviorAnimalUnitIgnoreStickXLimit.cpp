#include "Game/AI/Behavior/behaviorAnimalUnitIgnoreStickXLimit.h"

namespace uking::behavior {

AnimalUnitIgnoreStickXLimit::AnimalUnitIgnoreStickXLimit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AnimalUnitIgnoreStickXLimit::~AnimalUnitIgnoreStickXLimit() = default;

bool AnimalUnitIgnoreStickXLimit::m6(sead::Heap* heap) {
    return true;
}

void AnimalUnitIgnoreStickXLimit::m7() {}

void AnimalUnitIgnoreStickXLimit::loadParams() {

}

}  // namespace uking::behavior
