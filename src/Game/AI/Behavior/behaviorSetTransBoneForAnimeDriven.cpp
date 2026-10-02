#include "Game/AI/Behavior/behaviorSetTransBoneForAnimeDriven.h"

namespace uking::behavior {

SetTransBoneForAnimeDriven::SetTransBoneForAnimeDriven(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetTransBoneForAnimeDriven::~SetTransBoneForAnimeDriven() {
    ;
}

bool SetTransBoneForAnimeDriven::m6(sead::Heap* heap) {
    return true;
}

void SetTransBoneForAnimeDriven::m7() {}

void SetTransBoneForAnimeDriven::loadParams() {
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

}  // namespace uking::behavior
