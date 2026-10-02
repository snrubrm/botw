#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x71023d7eb0: listener for message 0x800007d (functions in the AssassinBossRootBase TU).
class Unk_71023d7eb0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x71023d7ee0: listener for message 0x800007e (functions in the AssassinBossRootBase TU).
class Unk_71023d7ee0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x71023d7e40: damage callback without RTTI of its own; keeps the enemy's life (plus the
// life recover info's extra HP) above _24.
class Unk_71023d7e40 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 0;
};

// vtable 0x71023d7e78: damage callback without RTTI of its own; damage from an "AssassinRockBall"
// attacker becomes _24 (type 22). `call` reads the attacker link from DamageManagerBase slot 37
// (declared as `s64 m37()`), so it is declared only.
class Unk_71023d7e78 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    s32 _24 = 0;
};

class AssassinBossRootBase : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinBossRootBase, EnemyRoot)
public:
    explicit AssassinBossRootBase(const InitArg& arg);
    ~AssassinBossRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual bool m45();
    virtual void m46();
    virtual void m47();

    // 0x710031bbc4 (not decompiled): creates the part actor `actor_name` registered as `part_name`
    // (with index `idx`).
    void sub_710031BBC4(const sead::SafeString& part_name, const sead::SafeString& actor_name,
                        s32 idx, sead::Heap* heap);

protected:
    // static_param at offset 0x1d8
    const int* mRockBallDamage_s{};
    // static_param at offset 0x1e0
    const float* mChangeModeLifeRatio_s{};
    Unk_71023d7eb0 _1e8;
    Unk_71023d7ee0 _220;
    f32 _258 = 0;
    Unk_71023d7e40 _260;
    Unk_71023d7e78 _288;
};
KSYS_CHECK_SIZE_NX150(AssassinBossRootBase, 0x2b0);

}  // namespace uking::ai
