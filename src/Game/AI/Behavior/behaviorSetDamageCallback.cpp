#include "Game/AI/Behavior/behaviorSetDamageCallback.h"

namespace uking::behavior {

SetDamageCallback::SetDamageCallback(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetDamageCallback::~SetDamageCallback() = default;

bool SetDamageCallback::m6(sead::Heap* heap) {
    return true;
}

void SetDamageCallback::m7() {}

void SetDamageCallback::m8() {
    setDamageCallbackTiming(mActor, *mTiming_s, m14());
}

void SetDamageCallback::m9() {
    sub_71005DA114(mActor, m14());
}

void SetDamageCallback::loadParams() {
    getStaticParam(&mTiming_s, "Timing");
}

}  // namespace uking::behavior
