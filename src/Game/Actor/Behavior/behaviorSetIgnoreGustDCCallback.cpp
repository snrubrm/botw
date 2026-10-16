#include "Game/Actor/Behavior/behaviorSetIgnoreGustDCCallback.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (the original stores the callback's 8 bytes at 0x50 first)
SetIgnoreGustDCCallback::SetIgnoreGustDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreGustDCCallback::~SetIgnoreGustDCCallback() = default;

bool SetIgnoreGustDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetIgnoreGustDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetIgnoreGustDCCallback::enter() {
    SetDamageCallback::enter();
}

void SetIgnoreGustDCCallback::leave() {
    SetDamageCallback::leave();
}

void SetIgnoreGustDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetIgnoreGustDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
