#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BalloonBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BalloonBase, ksys::act::ai::Action)
public:
    explicit BalloonBase(const InitArg& arg);
    ~BalloonBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual int m32();
    virtual float m33();

    ksys::act::BaseProcLink _20;
    // static_param at offset 0x30
    const float* mUpLimitSpeed_s{};
    // static_param at offset 0x38
    const float* mMaxAccel_s{};
    // static_param at offset 0x40
    const float* mMassScale_s{};
    // static_param at offset 0x48
    const float* mHeightLimit_s{};
    // static_param at offset 0x50
    const float* mBreakTimer_s{};
    // static_param at offset 0x58
    const float* mWindAccScale_s{};
    // static_param at offset 0x60
    const float* mWindSpdScale_s{};
    // static_param at offset 0x68
    const float* mStayAccScale_s{};
    // static_param at offset 0x70
    const float* mReturnStrengthFactor_s{};
    // static_param at offset 0x78
    const float* mRemainsHeightLimit_s{};
    // static_param at offset 0x80
    const bool* mIsChaseInitHeight_s{};
    // static_param at offset 0x88
    const bool* mReturnToOriginalPos_s{};
    // aitree_variable at offset 0x90
    int* mBalloonHungActorBaseProcID_a{};
    // aitree_variable at offset 0x98
    bool* mIsFlyingBalloon_a{};
    f32 _a0 = 1.0f;
    f32 _a4 = 0;
    f32 _a8 = 0;
    f32 _ac = 1.0f;
    f32 _b0 = 1.0f;
    bool _b4 = false;
    bool _b5 = false;
    ksys::act::BaseProcLink _b8;
    ksys::act::Actor* _c8 = mActor;
    ksys::Timer _d0{0, 0};
    u32 _dc;
    sead::Vector3f _e0 = sead::Vector3f::zero;
};

}  // namespace uking::action
