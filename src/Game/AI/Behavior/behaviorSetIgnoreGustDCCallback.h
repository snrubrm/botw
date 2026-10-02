#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetIgnoreGustDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetIgnoreGustDCCallback, SetDamageCallback)
public:
    explicit SetIgnoreGustDCCallback(const InitArg& arg);
    ~SetIgnoreGustDCCallback() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451ac0 _30;
};
KSYS_CHECK_SIZE_NX150(SetIgnoreGustDCCallback, 0x58);

}  // namespace uking::behavior
