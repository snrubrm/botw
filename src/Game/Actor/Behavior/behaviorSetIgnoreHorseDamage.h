#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetIgnoreHorseDamage : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetIgnoreHorseDamage, SetDamageCallback)
public:
    explicit SetIgnoreHorseDamage(const InitArg& arg);
    ~SetIgnoreHorseDamage() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451a50 _30;
};
KSYS_CHECK_SIZE_NX150(SetIgnoreHorseDamage, 0x58);

}  // namespace uking::behavior
