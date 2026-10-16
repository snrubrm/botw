#include "Game/Actor/Behavior/behaviorSetAcceptOnlyBombDCCallback.h"

namespace uking::behavior {

SetAcceptOnlyBombDCCallback::SetAcceptOnlyBombDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetAcceptOnlyBombDCCallback::~SetAcceptOnlyBombDCCallback() = default;

bool SetAcceptOnlyBombDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetAcceptOnlyBombDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetAcceptOnlyBombDCCallback::enter() {
    SetDamageCallback::enter();
    _40._24 = *mParams.mIsThroughEffectiveDamage_s;
    _40._25 = *mParams.mIsThroughDieAttribute_s;
}

void SetAcceptOnlyBombDCCallback::leave() {
    SetDamageCallback::leave();
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
