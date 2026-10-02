#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class AcceptLSwordDamageDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(AcceptLSwordDamageDCCallback, SetDamageCallback)
public:
    explicit AcceptLSwordDamageDCCallback(const InitArg& arg);
    ~AcceptLSwordDamageDCCallback() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451858 _30;
};
KSYS_CHECK_SIZE_NX150(AcceptLSwordDamageDCCallback, 0x58);

}  // namespace uking::behavior
