#include "Game/AI/Behavior/behaviorAwarenessDarkAreaIgnore.h"

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

}  // namespace uking::behavior
