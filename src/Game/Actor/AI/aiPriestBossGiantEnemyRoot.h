#pragma once

#include "KingSystem/ActorSystem/actActorAtk.h"

#include <xlink2/xlink2HandleSLink.h>
#include <prim/seadDelegate.h>
#include "Game/Actor/AI/aiPriestBossActorEnemyRoot.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102357d20.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

class Unk_7102450fa8;

namespace uking::ai {

class PriestBossGiantEnemyRoot;

// Placeholder name (vtable 0x71024137d0; inherits DamageCallback's RTTI; D1 0x7100519da4,
// D0 0x710051b574, `call` 0x7100519ea0). PriestBossGiantEnemyRoot::_2e8.
class Unk_71024137d0 : public act::DamageCallback {
public:
    ~Unk_71024137d0() override;
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) override;
    // 0x710051a000: classifies the hit into _24 (0 none, 1 hat hit, 2 / 3 hat hit by the iron ball (3: thrown back by
    // the owner, sub_710051A53C), 4 / 5 damage kind 3 (5: attacker tagged 0x5e27ef10), 6 iron ball elsewhere).
    void sub_710051A000(u32 kind);
    // 0x710051a434: the attack info of the current damage (sub_71007A255C(enemy, DamageManager::_6c)), or null.
    ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_710051A434();
    // 0x710051a53c: whether the attacker of `info` is one of the owner's units 11 - 18 whose bit is set in _28.
    bool sub_710051A53C(ksys::act::ActorAtk::Unk_710079e64c::Unk1* info);

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
class Unk_7102413808 : public act::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) override;
    void sub_710051A6B8();

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
    void calc_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool m35() override;
    bool m45() override;
    bool m46() override;
    bool m47() override;
    void m49() override;
    bool m51() override;
    bool m52() override;
    bool m53() override;
    virtual void m54();

    // Bound to _2e8._40 by enter_.
    void sub_710051AD38(s32 x);
    void sub_710051B0F8();

protected:
    // static_param at offset 0x230
    const int* mInvalidateIronBallDamageFrame_s{};
    // aitree_variable at offset 0x238
    bool* mPriestBossDownSideASPlaying_a{};
    // aitree_variable at offset 0x240
    void* mPriestBossMetaAIUnit_a{};
    Unk_71007214A0 _248;
    Unk_7102409958 _268{0x80000da};
    Unk_71024509d8 _2a8;
    Unk_71024137d0 _2e8;
    Unk_7102413808 _368;
    xlink2::HandleSLink _398;
};
KSYS_CHECK_SIZE_NX150(PriestBossGiantEnemyRoot, 0x3a8);

}  // namespace uking::ai
