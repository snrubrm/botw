#include "Game/AI/Behavior/behaviorSetAllNoDamageDCCallback.h"

namespace uking::behavior {

SetAllNoDamageDCCallback::SetAllNoDamageDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetAllNoDamageDCCallback::~SetAllNoDamageDCCallback() = default;

bool SetAllNoDamageDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetAllNoDamageDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetAllNoDamageDCCallback::m8() {
    SetDamageCallback::m8();
}

void SetAllNoDamageDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetAllNoDamageDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetAllNoDamageDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
