#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::behavior {

// vtable 0x7102439db0 (functions in this behavior's translation unit).
class Unk_7102439db0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102439db0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

class SetPlayerLargeAttackDeathDCCB : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetPlayerLargeAttackDeathDCCB, SetDamageCallback)
public:
    explicit SetPlayerLargeAttackDeathDCCB(const InitArg& arg);
    ~SetPlayerLargeAttackDeathDCCB() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102439db0 _30;
};
KSYS_CHECK_SIZE_NX150(SetPlayerLargeAttackDeathDCCB, 0x58);

}  // namespace uking::behavior
