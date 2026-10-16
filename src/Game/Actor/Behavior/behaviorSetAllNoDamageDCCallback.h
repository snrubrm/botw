#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetAllNoDamageDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetAllNoDamageDCCallback, SetDamageCallback)
public:
    explicit SetAllNoDamageDCCallback(const InitArg& arg);
    ~SetAllNoDamageDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_71024519a8 _30;
};
KSYS_CHECK_SIZE_NX150(SetAllNoDamageDCCallback, 0x58);

}  // namespace uking::behavior
