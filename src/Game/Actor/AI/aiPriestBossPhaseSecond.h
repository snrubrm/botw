#pragma once

#include <container/seadObjArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/Actor/AI/aiPriestBossPhase.h"
#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossPhaseSecond : public PriestBossPhase {
    SEAD_RTTI_OVERRIDE(PriestBossPhaseSecond, PriestBossPhase)
public:
    // Bits of _bb0 (tested through a stack temporary, SEAD_ENUM style).
    SEAD_ENUM(StateFlag, _0, _1, _2)
    // Argument of sub_710052B4D0 (stored to the stack on entry, SEAD_ENUM style).
    SEAD_ENUM(Mode, _0, _1, _2)

    explicit PriestBossPhaseSecond(const InitArg& arg);
    ~PriestBossPhaseSecond() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void m34() override {}
    bool m36() override { return PriestBossPhase::m36(); }
    bool m37(f32* ratio) override;
    Flag m38() override { return Flag::_1; }
    void m39() override;
    void m40() override;
    virtual void m41();

    // 0x710052b4d0
    void sub_710052B4D0(Mode mode);
    // 0x710052bac8: whether the member has taken damage; adds it to _130 once the mode change block time is over
    bool sub_710052BAC8(const ksys::act::ActorLinkConstDataAccess* accessor);
    // 0x710052bc04: runs the current formation; picks a new one when it is done
    void sub_710052BC04();
    // 0x710052c350: picks a formation record by weight (not the current one) and starts it
    void sub_710052C350();
    // 0x710052c44c: starts formation `id` (1: circle shoot, 2: circle rush, 3: line fall, 4: line rush)
    void sub_710052C44C(s32 id);

    // inline-only in the original; names are guesses (sub_710052B4D0 and handleMessage_: the flag index
    // temporaries share one stack slot, as inlined by-value parameters do)
    bool isStateFlagOn(StateFlag flag) const { return _bb0.isOnBit(flag); }
    void setStateFlag(StateFlag flag) { _bb0.setBit(flag); }
    void resetStateFlag(StateFlag flag) { _bb0.resetBit(flag); }

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
        s32 id = 0;
        f32 value = 0;
        f32 _8 = 0;  // weight (0x710052c350 picks a record by it)
        s32 _c = 0;  // times picked
    };
    // 0x710052c738: recomputes the record weights (less likely the more often picked), normalised to 1
    static void sub_710052C738(sead::ObjArray<PhaseRecord>* records);
    /* 0x690 */ sead::ObjArray<PhaseRecord> mRecords;
    /* 0x6b0 */ s32 _6b0 = 0;
    /* 0x6b8 */ Unk_7102450fe0* _6b8 = nullptr;  // current formation (_6c0 or _958; handleMessage_ forwards to m9)
    /* 0x6c0 */ Unk_7102450e00 _6c0;
    /* 0x958 */ Unk_7102450ed8 _958;
    /* 0xb58 */ Unk_71024508e8 _b58;
    /* 0xbb0 */ sead::BitFlag32 _bb0;
};

KSYS_CHECK_SIZE_NX150(PriestBossPhaseSecond, 0xbb8);

}  // namespace uking::ai
