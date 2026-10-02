#pragma once

#include <prim/seadBitFlag.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::act {

class LastBoss;

// Placeholder name (vtable 0x71023ce678; inherits DamageCallback's RTTI; `call` 0x71002c47e8, CSV
// LastBossX::x). LastBoss::_14f8. Same layout as SiteBoss's damage callback.
// TODO: incomplete.
class Unk_71023ce678 : public dmg::DamageCallback {
public:
    explicit Unk_71023ce678(LastBoss* boss) : mBoss(boss) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    /* 0x28 */ LastBoss* mBoss;
    /* 0x30 */ sead::BitFlag16 _30;  // LastBoss + 0x1528 (isGuardJust: bit 0)
    /* 0x34 */ u32 _34 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023ce678, 0x38);

// Name from the CSV (LastBoss::*): Calamity Ganon. vtable 0x71023ce070 (181 slots, no new virtuals),
// RTTI static 0x71025b3398 (parent: Enemy). Factory 0x71002c40e0 (CSV LastBoss::construct, which
// inlines the ctor): new(0x1e58).
// TODO: incomplete. Members are public: AI code reads them directly.
class LastBoss : public Enemy {
    SEAD_RTTI_OVERRIDE(LastBoss, Enemy)
public:
    explicit LastBoss(const CreateArg& arg);
    ~LastBoss() override;

    void m63() override;
    void initMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m77(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m117() override;
    bool m140() override;
    bool isGuard() override;
    bool isGuardJust() override;
    Unk_71025ae680* m178(sead::Heap* heap) override;

    // CSV names; called by LastBoss / Ganon AI.
    void stunEnd();
    void update();
    // 0x71002c5f18 (CSV LastBoss::x; declaration only): called by GanonShockRoot::leave_.
    void x();
    bool sub_71002C6210(f32 value) const;

    /* 0x14c8 */ void* _14c8 = nullptr;
    /* 0x14d0 */ u32 _14d0 = 0;
    /* 0x14d4 */ u32 _14d4;  // 0x14d4-0x14e4 not initialised by the ctor
    /* 0x14d8 */ u64 _14d8;
    /* 0x14e0 */ u32 _14e0;
    /* 0x14e4 */ u32 _14e4 = 0;
    /* 0x14e8 */ sead::BitFlag32 _14e8;  // ~55 AI accesses
    /* 0x14ec */ u32 _14ec = 0;
    /* 0x14f0 */ f32 _14f0 = 0;
    /* 0x14f8 */ Unk_71023ce678 _14f8{this};
    /* 0x1530 */ s32 _1530 = 0;
    /* 0x1534 */ s32 _1534 = 0;  // LastBossStun compares _1538 > _1534 and _1540 > _153c
    /* 0x1538 */ s32 _1538 = 0;
    /* 0x153c */ s32 _153c = 0;
    /* 0x1540 */ s32 _1540 = 0;
    /* 0x1544 */ s32 _1544 = 0;
    /* 0x1548 */ ksys::evt::ResidentEvent _1548;
    /* 0x1718 */ ksys::evt::ResidentEvent _1718;
    /* 0x18e8 */ ksys::evt::ResidentEvent _18e8;
    /* 0x1ab8 */ ksys::evt::ResidentEvent _1ab8;
    /* 0x1c88 */ ksys::evt::ResidentEvent _1c88;
};
KSYS_CHECK_SIZE_NX150(LastBoss, 0x1e58);

}  // namespace uking::act
