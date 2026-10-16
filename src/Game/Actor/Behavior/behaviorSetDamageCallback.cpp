#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"

namespace uking::behavior {

SetDamageCallback::SetDamageCallback(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetDamageCallback::~SetDamageCallback() = default;

bool SetDamageCallback::init_(sead::Heap* heap) {
    return true;
}

void SetDamageCallback::calc() {}

void SetDamageCallback::enter() {
    setDamageCallbackTiming(mActor, *mTiming_s, m14());
}

void SetDamageCallback::leave() {
    sub_71005DA114(mActor, m14());
}

void SetDamageCallback::loadParams() {
    getStaticParam(&mTiming_s, "Timing");
}

}  // namespace uking::behavior
