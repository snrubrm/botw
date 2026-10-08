#pragma once

#include <prim/seadBitFlag.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::act {

class LastBoss;

// Placeholder name (vtable 0x71023ce678; inherits DamageCallback's RTTI; `call` 0x71002c47e8, CSV
// LastBossX::x). LastBoss::_14f8. Same layout as SiteBoss's damage callback.
// TODO: incomplete.
class Unk_71023ce678 : public dmg::DamageCallback {
public:
    explicit Unk_71023ce678(LastBoss* boss) : mBoss(boss) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;

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

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void m63() override;
    void initMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m77(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m117(ksys::act::Unk117* arg) override;
    bool m140() override;
    bool isGuard() override;
    bool isGuardJust() override;
    Unk_71025ae680* m178(sead::Heap* heap) override;

    // CSV names; called by LastBoss / Ganon AI.
    void stunEnd();
    // 0x71002c5b3c / 0x71002c6a78 (placeholder names): set / clear Unk_710244eb48::_1c on the controller (m159).
    void sub_71002C5B3C();
    void sub_71002C6A78();
    void update();
    // 0x71002c5f18 (CSV LastBoss::x; declaration only): called by GanonShockRoot::leave_.
    void x();
    bool sub_71002C6210(f32 value) const;
    // 0x71002c5a14 / 0x71002c5db4 (lane1 s23, placeholder names): unload the loaded resident events
    // (_1548, _1718, _18e8 / _1ab8, _1c88).
    void sub_71002C5A14();
    void sub_71002C5DB4();
    // 0x71002c69cc / 0x71002c6a24 (lane1 s23, placeholder names): register / unregister the damage callback
    // `_14f8` with the actor's damage manager (timing 4).
    void sub_71002C69CC();
    void sub_71002C6A24();
    // 0x71002c6930 (placeholder name): deleteLater on every part actor (`_1128`) that is in its calc state.
    void sub_71002C6930();

    // The "WarpCharge" effect handle (LastBossPreNormalWarp::enter_). 0x14d4-0x14e4 are not initialised by the ctor.
    /* 0x14c8 */ xlink2::HandleELink _14c8;
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

// Accessor-based wrappers in the LastBoss TU (lane4 s44; placeholder names, the CSV has none).
// 0x71002c6b30: the accessor's actor as a LastBoss (null otherwise). 0x71002c6b0c: `_14e4 == 1` (false without one).
uking::act::LastBoss* sub_71002C6B30(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71002C6B0C(const ksys::act::ActorConstDataAccess& accessor);
// 0x71002c64a0 (placeholder name): the point 2 units from the actor towards the up-axis component
// perpendicular to its offset from the home position.
void sub_71002C64A0(sead::Vector3f* out, ksys::act::Actor* actor);
// 0x71002c682c (placeholder name): ActorConstDataAccess::sub_7100D153A4(value) on every part actor (Enemy::_1128) of
// `actor` that is in its calc state.
void sub_71002C682C(ksys::act::Actor* actor, f32 value);
