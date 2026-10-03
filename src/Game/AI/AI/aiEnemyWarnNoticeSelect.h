#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWarnNoticeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyWarnNoticeSelect, ksys::act::ai::Ai)
public:
    explicit EnemyWarnNoticeSelect(const InitArg& arg);
    ~EnemyWarnNoticeSelect() override;
    bool isChangeable() const override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m34();

protected:
    // static_param at offset 0x38
    const int* mWarnNoticeTime_s{};
    // static_param at offset 0x40
    const int* mWarnNoticeTimeRnd_s{};
    // static_param at offset 0x48
    const int* mWarnBlinkTime_s{};
    // static_param at offset 0x50
    const int* mLostCounter_s{};
    // static_param at offset 0x58
    const int* mPenaltyStair2Num_s{};
    // static_param at offset 0x60
    const float* mMaxCountUp_s{};
    // static_param at offset 0x68
    const float* mPenalty_s{};
    // static_param at offset 0x70
    const int* mNoPenaltyNum_s{};
    // static_param at offset 0x78
    const bool* mIsSight_s{};
    // static_param at offset 0x80
    const bool* mIsWorry_s{};
    // dynamic_param at offset 0x88
    bool* mForceNotice_d{};
    // dynamic_param at offset 0x90
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x98
    bool* mIsTrgChangeUnderWaterState_a{};
    f32 _a0{};
    s32 _a4{};
    s32 _a8{};
    f32 _ac{};
    s32 _b0{};
    s32 _b4{};
    Unk_7102450528 _b8;
    f32 _130 = 0;
    u32 _134 = 0;
    bool _138 = false;
    bool _139 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyWarnNoticeSelect, 0x140);

}  // namespace uking::ai
