#pragma once

#include <math/seadVector.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BoomerangMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BoomerangMove, ksys::act::ai::Action)
public:
    explicit BoomerangMove(const InitArg& arg);
    ~BoomerangMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    void sub_71000CB538(f32 gravity_factor);

    // static_param at offset 0x20
    const float* mPreCurveTimer_s{};
    // static_param at offset 0x28
    const float* mRadSpeed_s{};
    // static_param at offset 0x30
    const float* mCurveSpeedRate_s{};
    // static_param at offset 0x38
    const float* mStraightSpeedRate_s{};
    // static_param at offset 0x40
    const float* mCurvePredictFrame_s{};
    // static_param at offset 0x48
    const float* mCurveCheckYDist_s{};
    // static_param at offset 0x50
    const float* mStraightPredictFrame_s{};
    // static_param at offset 0x58
    const float* mStraightCheckYDist_s{};
    // static_param at offset 0x60
    const float* mFlyLimitTime_s{};
    // static_param at offset 0x68
    sead::SafeString mCatchAttentionName_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mTargetOffset_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    f32 _88 = 0.0f;
    f32 _8c = 1.0f;
    u64 _90 = 0;
    u64 _98 = 0;
    u64 _a0 = 0;
    u64 _a8 = 0;
    u64 _b0 = 0;
    u64 _b8 = 0;
    u64 _c0 = 0;
    u64 _c8 = 0;
    ksys::VFRValue _d0;
    sead::Vector3f _dc = sead::Vector3f::zero;
    f32 _e8 = 0.0f;
    f32 _ec = 1.0f;
};
KSYS_CHECK_SIZE_NX150(BoomerangMove, 0xf0);

}  // namespace uking::action
