#include "Game/AI/Behavior/behaviorAwarenessDarkAreaIgnore.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AwarenessDarkAreaIgnore::AwarenessDarkAreaIgnore(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AwarenessDarkAreaIgnore::~AwarenessDarkAreaIgnore() = default;

bool AwarenessDarkAreaIgnore::m6(sead::Heap* heap) {
    return true;
}

void AwarenessDarkAreaIgnore::m7() {}

void AwarenessDarkAreaIgnore::loadParams() {

}

void AwarenessDarkAreaIgnore::m8() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 |= 8;
}

void AwarenessDarkAreaIgnore::m9() {
    if (auto* awareness = mActor->getAwareness())
        awareness->_334 &= ~8;
}

}  // namespace uking::behavior
