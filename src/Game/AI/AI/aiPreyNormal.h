#pragma once

#include <container/seadRingBuffer.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PreyNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyNormal, ksys::act::ai::Ai)
public:
    explicit PreyNormal(const InitArg& arg);
    ~PreyNormal() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mChangeBattleStateRadius_s{};
    // static_param at offset 0x40
    const float* mCounterAttackRadius_s{};
    // static_param at offset 0x48
    const float* mCounterAttackRate_s{};
    // static_param at offset 0x50
    const float* mAddCautionLevelVal_s{};
    // static_param at offset 0x58
    const float* mAutoReduceCautionLevelVal_s{};
    // static_param at offset 0x60
    const float* mLimitOverReduceCautionLevelVal_s{};
    // static_param at offset 0x68
    const float* mAwnRangeScaleWhenAttention_s{};
    // static_param at offset 0x70
    const float* mTargetLostTime_s{};
    // static_param at offset 0x78
    const float* mAllowRoarRadius_s{};
    // static_param at offset 0x80
    const float* mEscapeWaterFlowLimit_s{};
    // static_param at offset 0x88
    const float* mNewFoodAddTime_s{};
    // static_param at offset 0x90
    const bool* mIsUseEscapeState_s{};
    // static_param at offset 0x98
    const bool* mIsPositiveAttacker_s{};
    // static_param at offset 0xa0
    const bool* mIsSearchTarget_s{};
    // static_param at offset 0xa8
    const bool* mIsEmitForceEscapeSignal_s{};
    // static_param at offset 0xb0
    const bool* mIsReceivedForceEscapeSignal_s{};
    // static_param at offset 0xb8
    const bool* mIsCheckSandStorm_s{};
    // map_unit_param at offset 0xc0
    const bool* mIsLocatorCreate_m{};
    // map_unit_param at offset 0xc8
    const bool* mEnableNoEntryAreaCheck_m{};
    /* 0x0d0 */ void* _d0 = nullptr;
    /* 0x0d8 */ void* _d8 = nullptr;
    /* 0x0e0 */ sead::Vector3f _e0;
    /* 0x0f0 */ void* _f0 = nullptr;
    /* 0x0f8 */ s32 _f8 = -1;
    /* 0x0fc */ s32 _fc = -1;
    /* 0x100 */ u32 _100 = 0;
    /* 0x104 */ u32 _104 = 0;
    /* 0x108 */ u32 _108 = 0;
    /* 0x10c */ u32 _10c = 0;
    /* 0x110 */ ksys::Timer _110;
    /* 0x11c */ ksys::Timer _11c;
    /* 0x128 */ u32 _128 = 0;
    /* 0x12c */ u32 _12c = 0;
    /* 0x130 */ u32 _130 = 0;
    /* 0x134 */ ksys::Timer _134;
    /* 0x140 */ ksys::Timer _140;
    /* 0x14c */ ksys::Timer _14c;
    /* 0x158 */ ksys::Timer _158;
    /* 0x164 */ sead::Vector3f _164;
    /* 0x170 */ ksys::act::BaseProcLink _170;
    /* 0x180 */ bool _180 = false;
    /* 0x181 */ bool _181 = true;
    /* 0x182 */ bool _182 = true;
    /* 0x183 */ bool _183 = false;
    /* 0x184 */ bool _184 = true;
    /* 0x188 */ s32 _188 = -1;
    /* 0x18c */ u16 _18c = 0;
    /* 0x18e */ u8 _18e = 0;
    /* 0x190 */ sead::Vector3f _190;
    /* 0x1a0 */ sead::FixedRingBuffer<f32, 5> _1a0;
    /* 0x1c8 */ Unk_710236f520 _1c8{mActor, 0x8000007};
    /* 0x1f8 */ Unk_7102450558 _1f8;
    /* 0x248 */ ksys::act::BaseProcLink _248;
    /* 0x258 */ u32 _258 = 0;
    /* 0x25c */ u32 _25c = 0;
    /* 0x260 */ u32 _260 = 0;
    /* 0x264 */ ksys::Timer _264;
    /* 0x270 */ bool _270 = false;
    /* 0x278 */ Unk_7102410070 _278{mActor, 0x80000a4};
    /* 0x2c0 */ Unk_71024504f8 _2c0;
    /* 0x320 */ u32 _320 = 0;
    /* 0x324 */ u32 _324;  // not initialised by the ctor
    /* 0x328 */ ksys::Timer _328;
    /* 0x334 */ ksys::Timer _334;
};
KSYS_CHECK_SIZE_NX150(PreyNormal, 0x340);

}  // namespace uking::ai
