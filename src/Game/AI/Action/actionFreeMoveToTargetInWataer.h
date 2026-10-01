#pragma once

#include <limits>
#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToTargetInWataer : public FreeMoveToTarget {
    SEAD_RTTI_OVERRIDE(FreeMoveToTargetInWataer, FreeMoveToTarget)
public:
    explicit FreeMoveToTargetInWataer(const InitArg& arg);
    ~FreeMoveToTargetInWataer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::phys::CharacterController* controller) override;
    void m33(ksys::phys::CharacterController* controller) override;
    bool m34() override;
    virtual void m38();

    sead::Vector3f _cc = {0, 0, 0};

    // static_param at offset 0xd8
    const float* mAllowMoveWaterDepth_s{};
    // static_param at offset 0xe0
    const float* mForceTurnLimitSpeedStream_s{};
    // static_param at offset 0xe8
    const bool* mIsForceTurnAgainstStream_s{};
    // static_param at offset 0xf0
    const bool* mForceUseFrontDir_s{};
    sead::Vector3f _f8{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                      std::numeric_limits<f32>::quiet_NaN()};
};

}  // namespace uking::action
