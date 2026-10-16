#include "Game/Actor/Behavior/behaviorSetIgnoreReboundDCCallback.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"

namespace uking::behavior {

SetIgnoreReboundDCCallback::SetIgnoreReboundDCCallback(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetIgnoreReboundDCCallback::~SetIgnoreReboundDCCallback() = default;

bool SetIgnoreReboundDCCallback::init_(sead::Heap* heap) {
    return true;
}

void SetIgnoreReboundDCCallback::calc() {}

void SetIgnoreReboundDCCallback::enter() {
    setDamageCallbackTiming(mActor, 1, &_40);
    _40._24.changeBit(0, *mParams.mEnableRebound_s);
    _40._24.changeBit(1, *mParams.mEnableReboundStrong_s);
    _40._24.changeBit(2, *mParams.mEnableReboundSuper_s);
}

void SetIgnoreReboundDCCallback::leave() {
    sub_71005DA114(mActor, &_40);
}

void SetIgnoreReboundDCCallback::loadParams() {
    getStaticParam(&mParams.mEnableRebound_s, "EnableRebound");
    getStaticParam(&mParams.mEnableReboundStrong_s, "EnableReboundStrong");
    getStaticParam(&mParams.mEnableReboundSuper_s, "EnableReboundSuper");
}

}  // namespace uking::behavior
