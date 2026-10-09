#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetAcceptOnlyBombDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetAcceptOnlyBombDCCallback, SetDamageCallback)
public:
    explicit SetAcceptOnlyBombDCCallback(const InitArg& arg);
    ~SetAcceptOnlyBombDCCallback() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    struct Params {
        const bool* mIsThroughEffectiveDamage_s{};
        const bool* mIsThroughDieAttribute_s{};
    };
    /* 0x30 */ Params mParams;
    /* 0x40 */ Unk_7102451890 _40;
};
KSYS_CHECK_SIZE_NX150(SetAcceptOnlyBombDCCallback, 0x68);

}  // namespace uking::behavior
