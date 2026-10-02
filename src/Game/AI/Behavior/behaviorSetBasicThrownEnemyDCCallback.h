#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// vtable 0x7102438dd0 (functions in this behavior's translation unit).
class Unk_7102438dd0 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102438dd0, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;  // not decompiled yet
};

// vtable 0x7102438e08 (functions in this behavior's translation unit).
class Unk_7102438e08 : public uking::dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102438e08, uking::dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;  // not decompiled yet
};

class SetBasicThrownEnemyDCCallback : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetBasicThrownEnemyDCCallback, ksys::act::ai::Behavior)
public:
    explicit SetBasicThrownEnemyDCCallback(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x7100638530)
    void m9() override;  // not decompiled yet (0x710063857c)
    ~SetBasicThrownEnemyDCCallback() override;  // not decompiled yet

    /* 0x28 */ Unk_7102451970 _28;
    /* 0x50 */ Unk_7102438dd0 _50;
    /* 0x78 */ Unk_7102438e08 _78;
};
KSYS_CHECK_SIZE_NX150(SetBasicThrownEnemyDCCallback, 0xa0);

}  // namespace uking::behavior
