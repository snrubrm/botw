#pragma once

#include "Game/AI/AI/aiNonPlayerHorseRide.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// The three damage callbacks of EnemyHorseRide (`_f8` / `_120` / `_148`, added to the actor's damage manager with the
// timings 4 / 1 / 5 by enter_). Placeholder names (vtable addresses; they inherit DamageCallback's RTTI). Their
// `call`s and D0s live in the EnemyHorseRide TU (0x7100396008-0x710039635c).
class Unk_71023e8328 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e8328, 0x28);

class Unk_71023e8360 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e8360, 0x28);

class Unk_71023e8398 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e8398, 0x28);

class EnemyHorseRide : public NonPlayerHorseRide {
    SEAD_RTTI_OVERRIDE(EnemyHorseRide, NonPlayerHorseRide)
public:
    explicit EnemyHorseRide(const InitArg& arg);
    ~EnemyHorseRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void m34() override;

protected:
    // static_param at offset 0xe0
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0xe8
    const int* mLowerBodyASSlot_s{};
    bool _f0 = false;
    Unk_71023e8328 _f8;
    Unk_71023e8360 _120;
    Unk_71023e8398 _148;
};
KSYS_CHECK_SIZE_NX150(EnemyHorseRide, 0x170);

}  // namespace uking::ai
