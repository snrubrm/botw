#include "Game/Actor/Behavior/behaviorSetGuardJustDamageCallback.h"

namespace uking::behavior {

SetGuardJustDamageCallback::SetGuardJustDamageCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetGuardJustDamageCallback::~SetGuardJustDamageCallback() = default;

bool SetGuardJustDamageCallback::init_(sead::Heap* heap) {
    if (!SetDamageCallback::init_(heap))
        return false;
    _38._24 = *mDamage_s;
    return true;
}

void SetGuardJustDamageCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mDamage_s, "Damage");
}

uking::act::DamageCallback* SetGuardJustDamageCallback::m14() {
    return &_38;
}

}  // namespace uking::behavior
