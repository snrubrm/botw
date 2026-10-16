#include "Game/Actor/Behavior/behaviorSetJustAvoidHit1DamageDCCB.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

SetJustAvoidHit1DamageDCCB::SetJustAvoidHit1DamageDCCB(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetJustAvoidHit1DamageDCCB::~SetJustAvoidHit1DamageDCCB() = default;

bool SetJustAvoidHit1DamageDCCB::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetJustAvoidHit1DamageDCCB::calc() {
    SetDamageCallback::calc();
}

void SetJustAvoidHit1DamageDCCB::enter() {
    SetDamageCallback::enter();
}

void SetJustAvoidHit1DamageDCCB::leave() {
    SetDamageCallback::leave();
}

void SetJustAvoidHit1DamageDCCB::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetJustAvoidHit1DamageDCCB::m14() {
    return &_30;
}

void Unk_7102439a60::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::act::DamageCallbackInfo* a6) {
    if (*a5 < 15)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(mDamageManager->mActor);
    if (enemy && enemy->_e84.isOnBit(0))
        *a1 = 1;
}

}  // namespace uking::behavior
