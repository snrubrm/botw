#include "Game/AI/Behavior/behaviorSetIgnoreMultiDamageDCCallback.h"

namespace uking::behavior {

SetIgnoreMultiDamageDCCallback::SetIgnoreMultiDamageDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetIgnoreMultiDamageDCCallback::~SetIgnoreMultiDamageDCCallback() = default;

// NON_MATCHING: cmp scheduled before the orr/and pair (regalloc)
bool SetIgnoreMultiDamageDCCallback::m6(sead::Heap* heap) {
    if (!SetDamageCallback::m6(heap))
        return false;
    _30._24.changeBit(0, *mEnableCritical_s);
    _30._24.changeBit(1, *mEnableSmallHit_s);
    _30._24.changeBit(2, *mEnableMiddleHit_s);
    _30._24.changeBit(3, *mEnableLargeHit_s);
    _30._24.changeBit(4, *mEnableBlowOff_s);
    _30._24.changeBit(5, *mEnableGust_s);
    return true;
}

void SetIgnoreMultiDamageDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetIgnoreMultiDamageDCCallback::m8() {
    SetDamageCallback::m8();
}

void SetIgnoreMultiDamageDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetIgnoreMultiDamageDCCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mEnableCritical_s, "EnableCritical");
    getStaticParam(&mEnableSmallHit_s, "EnableSmallHit");
    getStaticParam(&mEnableMiddleHit_s, "EnableMiddleHit");
    getStaticParam(&mEnableLargeHit_s, "EnableLargeHit");
    getStaticParam(&mEnableBlowOff_s, "EnableBlowOff");
    getStaticParam(&mEnableGust_s, "EnableGust");
}

uking::dmg::DamageCallback* SetIgnoreMultiDamageDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
