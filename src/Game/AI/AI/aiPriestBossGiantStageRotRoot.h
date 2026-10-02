#pragma once

#include <container/seadSafeArray.h>
#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantStageRotRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossGiantStageRotRoot, PriestBossMode)
public:
    explicit PriestBossGiantStageRotRoot(const InitArg& arg);
    ~PriestBossGiantStageRotRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m35(sead::Vector3f* out, s32 idx);

    void sub_710051D12C();
    void sub_710051D234();
    bool sub_710051D438();

protected:
    // static_param at offset 0x40
    const float* mCentralAngle_s{};
    // static_param at offset 0x48
    const float* mPercentRadiusHeight_s{};
    // static_param at offset 0x50
    const float* mIronBallHeightOffset_s{};
    // static_param at offset 0x58
    const float* mArcPercent_s{};
    // static_param at offset 0x60
    const float* mZOffset_s{};
    // static_param at offset 0x68
    const float* mZOffsetIndex_s{};
    // static_param at offset 0x70
    const float* mHoldBallsCounterLength_s{};
    // static_param at offset 0x78
    const float* mBallsReleaseIntervalFrames_s{};
    // aitree_variable at offset 0x80
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x88
    bool* mIsActive_a{};
    // aitree_variable at offset 0x90
    sead::Vector3f* mFacePos_a{};
    // aitree_variable at offset 0x98
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0xa0
    void* mPriestBossMetaAIUnit_a{};
    sead::SafeArray<Unk_7102368740, 8> _a8;
    Unk_7102372510 _428{mActor, 0x8000008};
    ksys::Timer _458{0, 0};
    s32 _464 = 0;
    bool _468 = false;
    s32 _46c = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossGiantStageRotRoot, 0x470);

}  // namespace uking::ai
