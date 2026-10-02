#include "Game/AI/Behavior/behaviorRagdollSmallDamageIdxChanger.h"

namespace uking::behavior {

RagdollSmallDamageIdxChanger::RagdollSmallDamageIdxChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
RagdollSmallDamageIdxChanger::~RagdollSmallDamageIdxChanger() {
    ;
}

bool RagdollSmallDamageIdxChanger::m6(sead::Heap* heap) {
    return true;
}

void RagdollSmallDamageIdxChanger::loadParams() {
    getStaticParam(&mIsChinkCheck_s, "IsChinkCheck");
    getStaticParam(&mKeyName_s, "KeyName");
}

}  // namespace uking::behavior
