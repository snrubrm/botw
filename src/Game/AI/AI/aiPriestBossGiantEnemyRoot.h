#pragma once

#include <prim/seadDelegate.h>
#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

class Unk_7102450fa8;

namespace uking::ai {

class PriestBossGiantEnemyRoot;

// Placeholder name (vtable 0x71024137d0; inherits DamageCallback's RTTI; D1 0x7100519da4,
// D0 0x710051b574, `call` 0x7100519ea0). PriestBossGiantEnemyRoot::_2e8.
class Unk_71024137d0 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 0;
    u32 _28 = 0;
    s32 _2c = 0;  // InvalidateIronBallDamageFrame (set by the owner's enter_)
    ksys::Timer _30{0, 0};
    sead::Delegate1<PriestBossGiantEnemyRoot, s32> _40;
    sead::DelegateR<PriestBossGiantEnemyRoot, Unk_7102450fa8*> _60;
};
KSYS_CHECK_SIZE_NX150(Unk_71024137d0, 0x80);

// Placeholder name (vtable 0x7102413808; inherits DamageCallback's RTTI; D0 0x710051b5bc,
// `call` 0x710051a640). PriestBossGiantEnemyRoot::_368.
class Unk_7102413808 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 1;
    s32 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102413808, 0x30);

class PriestBossGiantEnemyRoot : public PriestBossActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(PriestBossGiantEnemyRoot, PriestBossActorEnemyRoot)
public:
    explicit PriestBossGiantEnemyRoot(const InitArg& arg);
    ~PriestBossGiantEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m45() override;
    bool m46() override;
    bool m47() override;
    void m49() override;
    bool m52() override;
    bool m53() override;

    // Bound to _2e8._40 by enter_.
    void sub_710051AD38(s32 x);

protected:
    // static_param at offset 0x230
    const int* mInvalidateIronBallDamageFrame_s{};
    // aitree_variable at offset 0x238
    bool* mPriestBossDownSideASPlaying_a{};
    // aitree_variable at offset 0x240
    void* mPriestBossMetaAIUnit_a{};
    Unk_7102451120 _248;
    Unk_7102451148 _258;
    Unk_7102409958 _268{0x80000da};
    Unk_71024509d8 _2a8;
    Unk_71024137d0 _2e8;
    Unk_7102413808 _368;
    u64 _398 = 0;
    u32 _3a0 = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossGiantEnemyRoot, 0x3a8);

}  // namespace uking::ai
