#include "Game/AI/Behavior/behaviorSetDefenselessDCCallback.h"

namespace uking::behavior {

SetDefenselessDCCallback::SetDefenselessDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetDefenselessDCCallback::~SetDefenselessDCCallback() = default;

bool SetDefenselessDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetDefenselessDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetDefenselessDCCallback::m8() {
    SetDamageCallback::m8();
}

void SetDefenselessDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetDefenselessDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetDefenselessDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
