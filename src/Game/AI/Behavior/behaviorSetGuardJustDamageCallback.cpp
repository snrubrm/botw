#include "Game/AI/Behavior/behaviorSetGuardJustDamageCallback.h"

namespace uking::behavior {

SetGuardJustDamageCallback::SetGuardJustDamageCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetGuardJustDamageCallback::~SetGuardJustDamageCallback() = default;

bool SetGuardJustDamageCallback::m6(sead::Heap* heap) {
    if (!SetDamageCallback::m6(heap))
        return false;
    _38._24 = *mDamage_s;
    return true;
}

void SetGuardJustDamageCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mDamage_s, "Damage");
}

uking::dmg::DamageCallback* SetGuardJustDamageCallback::m14() {
    return &_38;
}

}  // namespace uking::behavior
