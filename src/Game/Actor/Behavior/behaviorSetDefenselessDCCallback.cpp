#include "Game/Actor/Behavior/behaviorSetDefenselessDCCallback.h"

namespace uking::behavior {

SetDefenselessDCCallback::SetDefenselessDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetDefenselessDCCallback::~SetDefenselessDCCallback() = default;

bool SetDefenselessDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetDefenselessDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetDefenselessDCCallback::enter() {
    SetDamageCallback::enter();
}

void SetDefenselessDCCallback::leave() {
    SetDamageCallback::leave();
}

void SetDefenselessDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetDefenselessDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
