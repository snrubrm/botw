#include "Game/AI/Behavior/behaviorSetIgnoreGustDCCallback.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (the original stores the callback's 8 bytes at 0x50 first)
SetIgnoreGustDCCallback::SetIgnoreGustDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreGustDCCallback::~SetIgnoreGustDCCallback() = default;

bool SetIgnoreGustDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetIgnoreGustDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetIgnoreGustDCCallback::m8() {
    SetDamageCallback::m8();
}

void SetIgnoreGustDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetIgnoreGustDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetIgnoreGustDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
