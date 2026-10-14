#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"
#include "Game/Actor/aiUnk_7102357210.h"

// Native PlayerNormal constructor 82E794 embeds this callback at +0x1b8.
// Its complete five-slot vtable is 0x710246ac48; D1 is DamageCallback's D2.
class Unk_710246ac48 : public uking::act::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_710246ac48, uking::act::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
              uking::act::DamageCallbackInfo* a6) override;
};

namespace uking::ai {

class PlayerNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerNormal, ksys::act::ai::Ai)
public:
    explicit PlayerNormal(const InitArg& arg);
    ~PlayerNormal() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x30];
    // static_param at offset 0x68
    const float* mEquipNoiseValue_s{};
    // static_param at offset 0x70
    const float* mAttackNoiseValue_s{};
    // static_param at offset 0x78
    const float* mArrowReadyNoiseValue_s{};
    // static_param at offset 0x80
    const float* mParashawlInvalidHeight_s{};
    // static_param at offset 0x88
    const float* mParashawlInvalidHeightSurfing_s{};
    // static_param at offset 0x90
    const float* mForceSlipSpeed_s{};
    // static_param at offset 0x98
    const float* mDoForbidTime_s{};
    // static_param at offset 0xa0
    const float* mNoRideJumpDiffY_s{};
    // static_param at offset 0xa8
    const float* mDashUpEnableSpeed_s{};
    // static_param at offset 0xb0
    const float* mEnergyPerChargeLv_s{};
    // static_param at offset 0xb8
    const float* mEnergyChargeStart_s{};
    // static_param at offset 0xc0
    const float* mWallSlipEnableSpeed_s{};
    // static_param at offset 0xc8
    const float* mCutAddSpeedRate_s{};
    // static_param at offset 0xd0
    const float* mCutAddSpeedMax_s{};
    // static_param at offset 0xd8
    const float* mCutAddSpeedDec_s{};
    // static_param at offset 0xe0
    const float* mHorseCallTime_s{};
    // static_param at offset 0xe8
    const float* mSwordSearchAngle_s{};
    // static_param at offset 0xf0
    const float* mDoClimbForbidTime_s{};
    // static_param at offset 0xf8
    const float* mDoClimbForbidAngVel_s{};
    // static_param at offset 0x100
    const float* mInWaterTimeForRagdoll_s{};
    // static_param at offset 0x108
    const float* mToFallHeightForJustRush_s{};

    // Native member lifetimes and vtables from 82E794 / 83E5CC.
    /* 0x110 */ Unk_71024507c8 _110{0x1800004};
    /* 0x150 */ Unk_7102450a68 _150;
    /* 0x1a8 */ bool _1a8 = false;
    /* 0x1a9 */ bool _1a9 = false;
    u8 _1aa[2];
    u8 _1ac[8];
    /* 0x1b4 */ f32 _1b4 = -1;
    /* 0x1b8 */ Unk_710246ac48 _1b8;
    /* 0x1e0 */ Unk_7102451900 _1e0;
    /* 0x208 */ Unk_7102451af8 _208;
    /* 0x230 */ f32 _230 = -1;
};
KSYS_CHECK_SIZE_NX150(PlayerNormal, 0x238);

}  // namespace uking::ai
