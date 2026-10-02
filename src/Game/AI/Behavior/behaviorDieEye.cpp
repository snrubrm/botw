#include "Game/AI/Behavior/behaviorDieEye.h"

namespace uking::behavior {

DieEye::DieEye(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
DieEye::~DieEye() {
    ;
}

bool DieEye::m6(sead::Heap* heap) {
    return true;
}

void DieEye::m7() {}

void DieEye::loadParams() {
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
