#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class CircleMoveInFluid : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CircleMoveInFluid, ksys::act::ai::Ai)
public:
    explicit CircleMoveInFluid(const InitArg& arg);
    ~CircleMoveInFluid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35(f32 a2, f32 a3, f32 a4);
    virtual void m36(sead::Vector3f* out);

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mRadiusX_s{};
    // static_param at offset 0x48
    const float* mRadiusZ_s{};
    // static_param at offset 0x50
    const float* mMinRandRadiusRate_s{};
    // static_param at offset 0x58
    const float* mMaxRandRadiusRate_s{};
    // static_param at offset 0x60
    const float* mAddAngleRateX_s{};
    // static_param at offset 0x68
    const float* mAddAngleRateZ_s{};
    // static_param at offset 0x70
    const float* mRandRangeY_s{};
    // static_param at offset 0x78
    const float* mRandRangeYOffest_s{};
    // static_param at offset 0x80
    const float* mLimitSpeedMoveY_s{};
    // static_param at offset 0x88
    const float* mChangeInterval_s{};
    // static_param at offset 0x90
    const float* mRandChangeInterval_s{};
    // static_param at offset 0x98
    const float* mReverseMoveRate_s{};
    // static_param at offset 0xa0
    const bool* mIsSetSystemDeleteDistance_s{};
    sead::Vector3f _a8;
    f32 _b4{};
    f32 _b8{};
    f32 _bc{};
    f32 _c0{};
    f32 _c4{};
    f32 _c8{};
    bool _cc{};
    ksys::Timer _d0;
};

}  // namespace uking::ai
