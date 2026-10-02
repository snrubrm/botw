#include "Game/AI/Behavior/behaviorSetIgnoreHorseDamage.h"

namespace uking::behavior {

SetIgnoreHorseDamage::SetIgnoreHorseDamage(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreHorseDamage::~SetIgnoreHorseDamage() = default;

bool SetIgnoreHorseDamage::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetIgnoreHorseDamage::m7() {
    SetDamageCallback::m7();
}

void SetIgnoreHorseDamage::m8() {
    SetDamageCallback::m8();
}

void SetIgnoreHorseDamage::m9() {
    SetDamageCallback::m9();
}

void SetIgnoreHorseDamage::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetIgnoreHorseDamage::m14() {
    return &_30;
}

}  // namespace uking::behavior
