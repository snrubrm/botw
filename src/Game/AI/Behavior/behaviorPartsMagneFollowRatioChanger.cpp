#include "Game/AI/Behavior/behaviorPartsMagneFollowRatioChanger.h"

namespace uking::behavior {

PartsMagneFollowRatioChanger::PartsMagneFollowRatioChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
PartsMagneFollowRatioChanger::~PartsMagneFollowRatioChanger() {
    ;
}

bool PartsMagneFollowRatioChanger::m6(sead::Heap* heap) {
    return true;
}

void PartsMagneFollowRatioChanger::m8() {}

void PartsMagneFollowRatioChanger::loadParams() {
    getStaticParam(&mRatio_s, "Ratio");
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::behavior
