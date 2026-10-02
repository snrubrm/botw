#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetGuardJustDamageCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetGuardJustDamageCallback, SetDamageCallback)
public:
    explicit SetGuardJustDamageCallback(const InitArg& arg);
    ~SetGuardJustDamageCallback() override;
    bool m6(sead::Heap* heap) override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ const int* mDamage_s{};
    /* 0x38 */ Unk_7102451938 _38;
};
KSYS_CHECK_SIZE_NX150(SetGuardJustDamageCallback, 0x60);

}  // namespace uking::behavior
