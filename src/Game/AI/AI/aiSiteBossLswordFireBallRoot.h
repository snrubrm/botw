#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossLswordFireBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordFireBallRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordFireBallRoot(const InitArg& arg);
    ~SiteBossLswordFireBallRoot() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPredictPosRate_s{};
    // static_param at offset 0x40
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x48
    const float* mKeepDistance_s{};
    // static_param at offset 0x50
    const float* mMoveSpeed_s{};
    // static_param at offset 0x58
    const float* mYOffset_s{};
    // static_param at offset 0x60
    const bool* mIsThrowChildDevice_s{};
    // static_param at offset 0x68
    const bool* mIsNeedCreateChildDevice_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mBindPosOffset_s{};
    // dynamic_param at offset 0x78
    sead::SafeString mThrowActorName_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x90
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _98 = false;
    s32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
    u32 _a8 = 0;
    u32 _ac = 0;
    u32 _b0 = 0;
    sead::Matrix34f _b4;
    gsys::BoneAccessKeyEx _e8;
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordFireBallRoot, 0x120);

}  // namespace uking::ai
