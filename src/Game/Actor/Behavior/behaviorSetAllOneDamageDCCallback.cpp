#include "Game/Actor/Behavior/behaviorSetAllOneDamageDCCallback.h"

namespace uking::behavior {

SetAllOneDamageDCCallback::SetAllOneDamageDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetAllOneDamageDCCallback::~SetAllOneDamageDCCallback() = default;

bool SetAllOneDamageDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetAllOneDamageDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetAllOneDamageDCCallback::enter() {
    SetDamageCallback::enter();
}

void SetAllOneDamageDCCallback::leave() {
    SetDamageCallback::leave();
}

void SetAllOneDamageDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetAllOneDamageDCCallback::m14() {
    return &_30;
}

void Unk_7102438b98::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::act::DamageCallbackInfo* a6) {
    if (*a1 >= 2)
        *a1 = 1;
}

}  // namespace uking::behavior
