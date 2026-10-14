#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MoveToTargetCollisionFeedback : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveToTargetCollisionFeedback, ksys::act::ai::Ai)
public:
    explicit MoveToTargetCollisionFeedback(const InitArg& arg);
    ~MoveToTargetCollisionFeedback() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCooldownFramesTargetAdjust_s{};
    // static_param at offset 0x40
    const float* mFramesUntilRetryOriginalPos_s{};
    // static_param at offset 0x48
    const float* mIdealDepthMin_s{};
    // static_param at offset 0x50
    const float* mIdealDepthMax_s{};
    // static_param at offset 0x58
    const float* mIgnoreYComponentThreshold_s{};
    // static_param at offset 0x60
    const bool* mUseMoveAwayFromPos_s{};
    // static_param at offset 0x68
    const bool* mRetryOriginalPos_s{};
    // static_param at offset 0x70
    const bool* mIsAdjustDepthOnCollision_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mMoveAwayFromPos_d{};
    ksys::Timer _88{0, 0};      // target adjust cooldown (CooldownFramesTargetAdjust)
    ksys::Timer _94{1, 1, 0};   // retry timer (FramesUntilRetryOriginalPos)
    sead::Vector3f _a0 = {0, 0, 0};
    f32 _ac = 1.0f;
};

}  // namespace uking::ai
