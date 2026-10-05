#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiRandomTimer.h"
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
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m34();
    // 0x71003c4ea4 / 0x71003c4cb4 / 0x71003c544c / 0x71003c56a8 (placeholder names; declared only)
    int sub_71003C4EA4();
    void sub_71003C4CB4(bool a1);
    bool sub_71003C544C();
    void sub_71003C56A8();

protected:
    void sub_71003C5B04(sead::Vector3f* position);
    bool sub_71003C5418(s32 condition);

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
    RandomTimer _a0;
    RandomTimer _ac;
    Unk_7102450528 _b8;
    f32 _130 = 0;
    u32 _134 = 0;
    bool _138 = false;
    bool _139 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyWarnNoticeSelect, 0x140);

}  // namespace uking::ai
