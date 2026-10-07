#pragma once

#include <container/seadObjArray.h>
#include "Game/AI/AI/aiPriestBossPhase.h"
#include "Game/AI/aiPriestBossPhaseMembers.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseSecond : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseSecond, PriestBossPhase)
public:
    explicit PriestBossPhaseSecond(const InitArg& arg);
    ~PriestBossPhaseSecond() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m34() override {}
    bool m36() override { return PriestBossPhase::m36(); }
    bool m37(f32* ratio) override;
    Flag m38() override { return Flag::_1; }
    void m39() override;
    void m40() override;

protected:
    // static_param at offset 0x80
    const int* mModeChangeLife_s{};
    // static_param at offset 0x88
    const int* mSimAtkMax_s{};
    // static_param at offset 0x90
    const int* mBowEquipMax_s{};
    // static_param at offset 0x98
    const int* mSyncAtkMax_s{};
    // static_param at offset 0xa0
    const float* mModeChangeBlockTime_s{};
    // static_param at offset 0xa8
    const float* mRespawnSpan_s{};
    // static_param at offset 0xb0
    const float* mRespawnBaseSpace_s{};
    // static_param at offset 0xb8
    const float* mRespawnBaseMoveTime_s{};
    // static_param at offset 0xc0
    const float* mRespawnBaseInterval_s{};
    // static_param at offset 0xc8
    const float* mCircleFormRange_s{};
    // static_param at offset 0xd0
    const float* mCircleFormRushWait_s{};
    // static_param at offset 0xd8
    const float* mCircleFormRushInterval_s{};
    // static_param at offset 0xe0
    const float* mCircleFormShootWait_s{};
    // static_param at offset 0xe8
    const float* mCircleFormShootInterval_s{};
    // static_param at offset 0xf0
    const float* mLineFormDistFromPlayer_s{};
    // static_param at offset 0xf8
    const float* mLineFormSpace_s{};
    // static_param at offset 0x100
    const float* mLineFormRushWait_s{};
    // static_param at offset 0x108
    const float* mLineFormRushInterval_s{};
    // static_param at offset 0x110
    const float* mLineFormFallWait_s{};
    // static_param at offset 0x118
    const float* mLineFormFallInterval_s{};
    // map_unit_param at offset 0x120
    const int* mPriestBossStartPhase_m{};
    /* 0x128 */ s32 _128 = 0;
    /* 0x12c */ f32 _12c = 0.0f;
    /* 0x130 */ s32 _130 = 0;
    /* 0x134 */ sead::SafeArray<u32, 9> _134;
    /* 0x158 */ Unk_7102451070 _158;
    /* 0x488 */ Unk_7102451050 _488;
    struct PhaseRecord {
        s32 id;
        f32 value;
        void* data;
    };
    /* 0x690 */ sead::ObjArray<PhaseRecord> mRecords;
    /* 0x6b0 */ s32 _6b0 = 0;
    /* 0x6b8 */ void* _6b8 = nullptr;
    /* 0x6c0 */ Unk_7102450e00 _6c0;
    u8 _8a0[0x958 - 0x8a0];
    /* 0x958 */ Unk_7102450ed8 _958;
    /* 0xb58 */ Unk_71024508e8 _b58;
    /* 0xbb0 */ u32 _bb0 = 0;
};

KSYS_CHECK_SIZE_NX150(PriestBossPhaseSecond, 0xbb8);

}  // namespace uking::ai
