#include "Game/AI/Behavior/behaviorAnimalUnitIgnoreStickXLimit.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void AnimalUnitIgnoreStickXLimit::m8() {
    if (auto* rideable = mActor->m132())
        rideable->_8 |= 0x100;
}

void AnimalUnitIgnoreStickXLimit::m9() {
    if (auto* rideable = mActor->m132())
        rideable->_8 &= ~0x100;
}

}  // namespace uking::behavior
