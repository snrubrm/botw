#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class addNoiseToTargetPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(addNoiseToTargetPos, ksys::act::ai::Ai)
public:
    explicit addNoiseToTargetPos(const InitArg& arg);
    ~addNoiseToTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71002F8D1C(sead::Vector3f* result, const sead::Vector3f& target,
                      const sead::Vector3f& noise);
    // static_param at offset 0x38
    const float* mRandYMin_s{};
    // static_param at offset 0x40
    const float* mRandYMax_s{};
    // static_param at offset 0x48
    const float* mRandLeftMax_s{};
    // static_param at offset 0x50
    const float* mRandRightMax_s{};
    // static_param at offset 0x58
    const float* mRandDistMin_s{};
    // static_param at offset 0x60
    const float* mRandDistMax_s{};
    // static_param at offset 0x68
    const bool* mIsUpdateEveryFrame_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _78;
};

}  // namespace uking::ai
