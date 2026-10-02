#include "Game/AI/Behavior/behaviorCloseEye.h"

namespace uking::behavior {

CloseEye::CloseEye(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
CloseEye::~CloseEye() {
    ;
}

bool CloseEye::m6(sead::Heap* heap) {
    return true;
}

void CloseEye::m7() {}

void CloseEye::loadParams() {
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
