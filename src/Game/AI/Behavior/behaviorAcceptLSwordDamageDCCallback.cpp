#include "Game/AI/Behavior/behaviorAcceptLSwordDamageDCCallback.h"

namespace uking::behavior {

AcceptLSwordDamageDCCallback::AcceptLSwordDamageDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

AcceptLSwordDamageDCCallback::~AcceptLSwordDamageDCCallback() = default;

uking::dmg::DamageCallback* AcceptLSwordDamageDCCallback::m14() {
    return &_30;
}

}  // namespace uking::behavior
