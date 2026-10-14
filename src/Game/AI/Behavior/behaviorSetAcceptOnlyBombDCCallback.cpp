#include "Game/AI/Behavior/behaviorSetAcceptOnlyBombDCCallback.h"

namespace uking::behavior {

SetAcceptOnlyBombDCCallback::SetAcceptOnlyBombDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetAcceptOnlyBombDCCallback::~SetAcceptOnlyBombDCCallback() = default;

bool SetAcceptOnlyBombDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetAcceptOnlyBombDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetAcceptOnlyBombDCCallback::m8() {
    SetDamageCallback::m8();
    _40._24 = *mParams.mIsThroughEffectiveDamage_s;
    _40._25 = *mParams.mIsThroughDieAttribute_s;
}

void SetAcceptOnlyBombDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetAcceptOnlyBombDCCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mParams.mIsThroughEffectiveDamage_s, "IsThroughEffectiveDamage");
    getStaticParam(&mParams.mIsThroughDieAttribute_s, "IsThroughDieAttribute");
}

uking::act::DamageCallback* SetAcceptOnlyBombDCCallback::m14() {
    return &_40;
}

}  // namespace uking::behavior
