#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetDistanceSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetDistanceSelect, ksys::act::ai::Ai)
public:
    explicit TargetDistanceSelect(const InitArg& arg);
    ~TargetDistanceSelect() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual float m34();

protected:
    void sub_71005BE078();
    void sub_71005BE164();

    // static_param at offset 0x38
    const float* mBoundaryDistance_s{};
    // static_param at offset 0x40
    const float* mOverlapDistance_s{};
    // static_param at offset 0x48
    const bool* mIsUpdateTarget_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
