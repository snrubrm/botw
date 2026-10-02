#include "Game/AI/Behavior/behaviorAwarenessScaleByASEvent.h"

namespace uking::behavior {

AwarenessScaleByASEvent::AwarenessScaleByASEvent(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AwarenessScaleByASEvent::~AwarenessScaleByASEvent() = default;

bool AwarenessScaleByASEvent::m6(sead::Heap* heap) {
    return true;
}

void AwarenessScaleByASEvent::m8() {}

void AwarenessScaleByASEvent::loadParams() {

}

}  // namespace uking::behavior
