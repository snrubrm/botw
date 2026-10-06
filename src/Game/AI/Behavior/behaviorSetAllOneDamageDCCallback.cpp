#include "Game/AI/Behavior/behaviorSetAllOneDamageDCCallback.h"

namespace uking::behavior {

SetAllOneDamageDCCallback::SetAllOneDamageDCCallback(const InitArg& arg) : SetDamageCallback(arg) {}

SetAllOneDamageDCCallback::~SetAllOneDamageDCCallback() = default;

bool SetAllOneDamageDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetAllOneDamageDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetAllOneDamageDCCallback::m8() {
    SetDamageCallback::m8();
}

void SetAllOneDamageDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetAllOneDamageDCCallback::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetAllOneDamageDCCallback::m14() {
    return &_30;
}

void Unk_7102438b98::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a1 >= 2)
        *a1 = 1;
}

}  // namespace uking::behavior
