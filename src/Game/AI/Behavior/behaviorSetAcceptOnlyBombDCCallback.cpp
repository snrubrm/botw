#include "Game/AI/Behavior/behaviorSetAcceptOnlyBombDCCallback.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (params at 0x30 / the callback bools)
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
    _40._24 = *mIsThroughEffectiveDamage_s;
    _40._25 = *mIsThroughDieAttribute_s;
}

void SetAcceptOnlyBombDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetAcceptOnlyBombDCCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mIsThroughEffectiveDamage_s, "IsThroughEffectiveDamage");
    getStaticParam(&mIsThroughDieAttribute_s, "IsThroughDieAttribute");
}

uking::dmg::DamageCallback* SetAcceptOnlyBombDCCallback::m14() {
    return &_40;
}

}  // namespace uking::behavior
