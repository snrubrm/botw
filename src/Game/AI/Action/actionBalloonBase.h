#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

namespace ksys::act {
class RopeBase;
}

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
    virtual bool m32();
    virtual float m33();
    virtual f32 m34(f32 current, f32 target, f32 step);
    // inline in the original (emitted out of line in this TU); signature is a guess
    virtual void m35(ksys::phys::RigidBody* a, ksys::phys::RigidBody* b, ksys::act::RopeBase* rope) {}

    void sub_71000B782C(f32 value);

    // Placeholder names (out-of-line copies of helpers that leave_ / calc_ inline).
    // 0x71000b8054: cuts the rope hung from the balloon, tells the hung actor it is released and clears
    // the hung actor id.
    void sub_71000B8054();
    // 0x71000b7980: the chemical (wind) vector of the actor, or zero (the vector part of m33, out of line).
    sead::Vector3f sub_71000B7980();
    // 0x71000b7f94: messages 0x3000011 to the rope actor unless the actor is held or its LOD flag is set.
    void sub_71000B7F94();
    // 0x71000b89dc: whether the actor is at or above the (remains) height limit.
    bool sub_71000B89DC() const;
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
