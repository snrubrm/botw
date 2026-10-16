#include "Game/Actor/Behavior/behaviorAnimalUnitIgnoreStickXLimit.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AnimalUnitIgnoreStickXLimit::AnimalUnitIgnoreStickXLimit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AnimalUnitIgnoreStickXLimit::~AnimalUnitIgnoreStickXLimit() = default;

bool AnimalUnitIgnoreStickXLimit::init_(sead::Heap* heap) {
    return true;
}

void AnimalUnitIgnoreStickXLimit::calc() {}

void AnimalUnitIgnoreStickXLimit::loadParams() {

}

void AnimalUnitIgnoreStickXLimit::enter() {
    if (auto* rideable = mActor->m132())
        rideable->_8 |= 0x100;
}

void AnimalUnitIgnoreStickXLimit::leave() {
    if (auto* rideable = mActor->m132())
        rideable->_8 &= ~0x100;
}

}  // namespace uking::behavior
