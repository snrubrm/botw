#include "Game/AI/Behavior/behaviorSetIgnoreReboundDCCallback.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling
SetIgnoreReboundDCCallback::SetIgnoreReboundDCCallback(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetIgnoreReboundDCCallback::~SetIgnoreReboundDCCallback() = default;

bool SetIgnoreReboundDCCallback::m6(sead::Heap* heap) {
    return true;
}

void SetIgnoreReboundDCCallback::m7() {}

void SetIgnoreReboundDCCallback::m8() {
    setDamageCallbackTiming(mActor, 1, &_40);
    _40._24.changeBit(0, *mEnableRebound_s);
    _40._24.changeBit(1, *mEnableReboundStrong_s);
    _40._24.changeBit(2, *mEnableReboundSuper_s);
}

void SetIgnoreReboundDCCallback::m9() {
    sub_71005DA114(mActor, &_40);
}

void SetIgnoreReboundDCCallback::loadParams() {
    getStaticParam(&mEnableRebound_s, "EnableRebound");
    getStaticParam(&mEnableReboundStrong_s, "EnableReboundStrong");
    getStaticParam(&mEnableReboundSuper_s, "EnableReboundSuper");
}

}  // namespace uking::behavior
