#include "Game/AI/Behavior/behaviorSetAttensionASEvent.h"

namespace uking::behavior {

SetAttensionASEvent::SetAttensionASEvent(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetAttensionASEvent::~SetAttensionASEvent() {
    ;
}

bool SetAttensionASEvent::m6(sead::Heap* heap) {
    return true;
}

void SetAttensionASEvent::loadParams() {
    getStaticParam(&mAttKey_s, "AttKey");
}

}  // namespace uking::behavior
