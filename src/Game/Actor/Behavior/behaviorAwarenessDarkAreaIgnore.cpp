#include "Game/Actor/Behavior/behaviorAwarenessDarkAreaIgnore.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AwarenessDarkAreaIgnore::AwarenessDarkAreaIgnore(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AwarenessDarkAreaIgnore::~AwarenessDarkAreaIgnore() = default;

bool AwarenessDarkAreaIgnore::init_(sead::Heap* heap) {
    return true;
}

void AwarenessDarkAreaIgnore::calc() {}

void AwarenessDarkAreaIgnore::loadParams() {

}

void AwarenessDarkAreaIgnore::enter() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 |= 8;
}

void AwarenessDarkAreaIgnore::leave() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 &= ~8;
}

}  // namespace uking::behavior
