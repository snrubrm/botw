#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReduceDistanceToTargetPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReduceDistanceToTargetPos, ksys::act::ai::Ai)
public:
    explicit ReduceDistanceToTargetPos(const InitArg& arg);
    ~ReduceDistanceToTargetPos() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_710053AF70();

    // static_param at offset 0x38
    const float* mDistanceScale_s{};
    // static_param at offset 0x40
    const float* mMinReduceDist_s{};
    // static_param at offset 0x48
    const float* mMaxReduceDist_s{};
    // static_param at offset 0x50
    const float* mMinDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
