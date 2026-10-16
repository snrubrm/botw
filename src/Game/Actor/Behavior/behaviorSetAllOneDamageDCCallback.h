#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"

namespace uking::behavior {

// vtable 0x7102438b98 (functions in this behavior's translation unit).
class Unk_7102438b98 : public uking::act::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102438b98, uking::act::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
              uking::act::DamageCallbackInfo* a6) override;
};

class SetAllOneDamageDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetAllOneDamageDCCallback, SetDamageCallback)
public:
    explicit SetAllOneDamageDCCallback(const InitArg& arg);
    ~SetAllOneDamageDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102438b98 _30;
};
KSYS_CHECK_SIZE_NX150(SetAllOneDamageDCCallback, 0x58);

}  // namespace uking::behavior
