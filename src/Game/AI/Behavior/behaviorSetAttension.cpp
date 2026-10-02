#include "Game/AI/Behavior/behaviorSetAttension.h"

namespace uking::behavior {

SetAttension::SetAttension(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetAttension::~SetAttension() {
    ;
}

bool SetAttension::m6(sead::Heap* heap) {
    return true;
}

void SetAttension::m7() {}

void SetAttension::loadParams() {
    getStaticParam(&mSetState_s, "SetState");
    getStaticParam(&mAttKey_s, "AttKey");
}

}  // namespace uking::behavior
