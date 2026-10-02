#include "Game/AI/Behavior/behaviorSignalControl.h"

namespace uking::behavior {

SignalControl::SignalControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SignalControl::~SignalControl() = default;

bool SignalControl::m6(sead::Heap* heap) {
    return true;
}

void SignalControl::m7() {}

void SignalControl::loadParams() {
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mIsOnOnEnter_s, "IsOnOnEnter");
    getStaticParam(&mIsReverseOnLeave_s, "IsReverseOnLeave");
}

}  // namespace uking::behavior
