#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InsectEscape, ksys::act::ai::Ai)
public:
    explicit InsectEscape(const InitArg& arg);
    ~InsectEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100449E98();
    bool sub_710044A218(const sead::Vector3f& dir, f32 distance);

protected:
    // static_param at offset 0x38
    const float* mRunAwayDistanceMax_s{};
    // static_param at offset 0x40
    const float* mRunAwayDistanceMin_s{};
    // static_param at offset 0x48
    const float* mRunAwayHeightOffset_s{};
    // static_param at offset 0x50
    const float* mAllowRandAngleVertical_s{};
    // static_param at offset 0x58
    const float* mAllowRandAngleHorizontal_s{};
    // static_param at offset 0x60
    const bool* mInWater_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _70;
    sead::Vector3f _7c;
    // 0x88-0x98: never accessed in the original
    u8 _88[0x10];
};

}  // namespace uking::ai
