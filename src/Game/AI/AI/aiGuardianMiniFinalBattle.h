#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiEnemyBattle.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {
class GuardianMiniFinalBattle;
}  // namespace uking::ai

// Damage callbacks owned by GuardianMiniFinalBattle (no RTTI of their own). Placeholder names are
// the vtable addresses.

// vtable 0x71023f86d8
class Unk_71023f86d8 : public uking::dmg::DamageCallback {
public:
    explicit Unk_71023f86d8(uking::ai::GuardianMiniFinalBattle* owner) : mOwner(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
              uking::dmg::DamageCallbackInfo* a6) override;

    uking::ai::GuardianMiniFinalBattle* mOwner;
};

// vtable 0x71023f8710
class Unk_71023f8710 : public uking::dmg::DamageCallback {
public:
    explicit Unk_71023f8710(uking::ai::GuardianMiniFinalBattle* owner) : mOwner(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
              uking::dmg::DamageCallbackInfo* a6) override;

    uking::ai::GuardianMiniFinalBattle* mOwner;
};

namespace uking::ai {

class GuardianMiniFinalBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(GuardianMiniFinalBattle, EnemyBattle)
public:
    explicit GuardianMiniFinalBattle(const InitArg& arg);
    ~GuardianMiniFinalBattle() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void changeToMoveBattleSign();

    void sub_710041B3D4();
    // 0x710041b978 (placeholder name): resets the three guard AS slots.
    void sub_710041B978();
    // 0x710041ba0c (placeholder name): starts the "FlashShader" AS and the final mode colour AS.
    void sub_710041BA0C();
    void m38() override;

protected:
    // static_param at offset 0x90
    const int* mASSlotRight_s{};
    // static_param at offset 0x98
    const int* mASSlotLeft_s{};
    // static_param at offset 0xa0
    const int* mASSlotBack_s{};
    // static_param at offset 0xa8
    const int* mAttackHitNum_s{};
    // static_param at offset 0xb0
    const bool* mIsPreAttackMove_s{};
    // static_param at offset 0xb8
    const float* mRotNeckRate_s{};
    // aitree_variable at offset 0xc0
    int* mGuardianMiniChanceTimeState_a{};
    sead::Vector3f _c8{0, 0, 0};
    s32 _d4{};
    bool _d8{};
    Unk_71023f86d8 _e0{this};
    Unk_71023f8710 _110{this};
};

}  // namespace uking::ai
