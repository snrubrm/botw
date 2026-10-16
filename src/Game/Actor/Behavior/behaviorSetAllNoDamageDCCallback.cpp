#include "Game/Actor/Behavior/behaviorSetAllNoDamageDCCallback.h"

namespace uking::behavior {

SetAllNoDamageDCCallback::SetAllNoDamageDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetAllNoDamageDCCallback::~SetAllNoDamageDCCallback() = default;

bool SetAllNoDamageDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetAllNoDamageDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetAllNoDamageDCCallback::enter() {
    SetDamageCallback::enter();
}

void SetAllNoDamageDCCallback::leave() {
    SetDamageCallback::leave();
}

void SetAllNoDamageDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetAllNoDamageDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
