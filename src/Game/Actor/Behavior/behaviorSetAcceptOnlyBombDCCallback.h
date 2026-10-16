#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetAcceptOnlyBombDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetAcceptOnlyBombDCCallback, SetDamageCallback)
public:
    explicit SetAcceptOnlyBombDCCallback(const InitArg& arg);
    ~SetAcceptOnlyBombDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    struct Params {
        const bool* mIsThroughEffectiveDamage_s{};
        const bool* mIsThroughDieAttribute_s{};
    };
    /* 0x30 */ Params mParams;
    /* 0x40 */ Unk_7102451890 _40;
};
KSYS_CHECK_SIZE_NX150(SetAcceptOnlyBombDCCallback, 0x68);

}  // namespace uking::behavior
