#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossSpearAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSpearAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSpearAttackRoot(const InitArg& arg);
    ~SiteBossSpearAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* pos);

protected:
    // static_param at offset 0x38
    const int* mThrowSpearRate_s{};
    // static_param at offset 0x40
    const int* mBeamRate_s{};
    // static_param at offset 0x48
    const int* mIceBulletRate_s{};
    // static_param at offset 0x50
    const int* mSweepRateAtFar_s{};
    // static_param at offset 0x58
    const int* mSweepRateAtNear_s{};
    // static_param at offset 0x60
    const float* mReturnWaitCount_s{};
    // static_param at offset 0x68
    const float* mBeamPatternChangeHP_s{};
    // static_param at offset 0x70
    const float* mFarDistanceAttackRange_s{};
    // static_param at offset 0x78
    const float* mNearDistanceAttackRange_s{};
    // static_param at offset 0x80
    const float* mVerticalAttackRange_s{};
    // static_param at offset 0x88
    const float* mOnIceBlockHeight_s{};
    // static_param at offset 0x90
    const bool* mIsBowAimedCounterOn_s{};
    // static_param at offset 0x98
    const bool* mIsIceBulletOn_s{};
    // static_param at offset 0xa0
    sead::SafeString mWarpAnchorFirstSuffix_s{};
    // static_param at offset 0xb0
    sead::SafeString mWarpAnchorAfterSuffix_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mChaseDistOffset_s{};
    // dynamic_param at offset 0xd0
    bool* mIsAttackPatternFixed_d{};
    bool _d8 = false;
    bool _d9 = false;
    bool _da = false;
    bool _db = false;
    bool _dc = false;
    s32 _e0 = 0;
    s32 _e4 = 0;
    s32 _e8 = 0;
    gsys::BoneAccessKeyEx _f0;
    ksys::Timer _128;
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearAttackRoot, 0x138);

}  // namespace uking::ai
