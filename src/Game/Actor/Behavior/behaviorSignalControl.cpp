#include "Game/Actor/Behavior/behaviorSignalControl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SignalControl::SignalControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SignalControl::~SignalControl() = default;

bool SignalControl::init_(sead::Heap* heap) {
    return true;
}

void SignalControl::calc() {}

void SignalControl::loadParams() {
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mIsOnOnEnter_s, "IsOnOnEnter");
    getStaticParam(&mIsReverseOnLeave_s, "IsReverseOnLeave");
}

void SignalControl::enter() {
    if (*mSignalType_s != 0)
        return;
    auto* actor = mActor;
    if (*mIsOnOnEnter_s)
        actor->emitBasicSigOn();
    else
        actor->emitBasicSigOff();
}

void SignalControl::leave() {
    if (!*mIsReverseOnLeave_s)
        return;
    if (*mSignalType_s != 0)
        return;
    auto* actor = mActor;
    if (*mIsOnOnEnter_s)
        actor->emitBasicSigOff();
    else
        actor->emitBasicSigOn();
}

}  // namespace uking::behavior
