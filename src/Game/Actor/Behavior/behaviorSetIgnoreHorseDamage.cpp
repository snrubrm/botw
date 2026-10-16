#include "Game/Actor/Behavior/behaviorSetIgnoreHorseDamage.h"

namespace uking::behavior {

SetIgnoreHorseDamage::SetIgnoreHorseDamage(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreHorseDamage::~SetIgnoreHorseDamage() = default;

bool SetIgnoreHorseDamage::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetIgnoreHorseDamage::calc() {
    SetDamageCallback::calc();
}

void SetIgnoreHorseDamage::enter() {
    SetDamageCallback::enter();
}

void SetIgnoreHorseDamage::leave() {
    SetDamageCallback::leave();
}

void SetIgnoreHorseDamage::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetIgnoreHorseDamage::m14() {
    return &_30;
}

}  // namespace uking::behavior
