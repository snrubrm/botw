#include "Game/AI/Behavior/behaviorAwarenessScaleByASEvent.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void AwarenessScaleByASEvent::m9() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);
}

}  // namespace uking::behavior
