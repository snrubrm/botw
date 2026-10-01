#pragma once

#include "Game/AI/Action/actionBackStepToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStepToTargetPos : public BackStepToTarget {
    SEAD_RTTI_OVERRIDE(BackStepToTargetPos, BackStepToTarget)
public:
    explicit BackStepToTargetPos(const InitArg& arg);
    ~BackStepToTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m33(sead::Vector3f* dir, const sead::Vector3f& up) override;
    void m34() override;
    void m35() override;
    void m36() override;
    void m37() override;
    void m41(f32* a, sead::Vector3f* b) override;
    f32 m42() override;

    // static_param at offset 0xc0
    const bool* mIsJumpHeightFromHigherPos_s{};
    // static_param at offset 0xc8
    sead::SafeString mStartAS_s{};
    // static_param at offset 0xd8
    sead::SafeString mLoopAS_s{};
    // static_param at offset 0xe8
    sead::SafeString mPreLandAS_s{};
    // static_param at offset 0xf8
    sead::SafeString mEndAS_s{};
    sead::Vector3f _108 = {0, 0, 0};
};

}  // namespace uking::action
