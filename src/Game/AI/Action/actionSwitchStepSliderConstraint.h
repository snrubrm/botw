#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace ksys::phys {
class Constraint;
class RigidBody;
}

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace uking::action {

class SwitchStepSliderConstraint : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchStepSliderConstraint, ksys::act::ai::Action)
public:
    explicit SwitchStepSliderConstraint(const InitArg& arg);
    ~SwitchStepSliderConstraint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;

protected:
    void calc_() override;
    // Called with the slider position: switches on (emitBasicSigOn, "on" SLink, OnASName) after the
    // timer _a8 ran out at the bottom, off when it moves up.
    virtual void m32(f32 value);
    // Applies the impulse to the slider body (Once: moves the body to `pos` once the switch is on).
    virtual void m33(ksys::phys::RigidBody* body, const sead::Vector3f* impulse,
                     const sead::Vector3f* pos);
    // Plays OffASName.
    virtual void m34();
    // 0x710028ee24 / 0x710028ee98: play OnASName / OffASName (if set).
    void sub_710028EE24();
    void sub_710028EE98();

    ksys::phys::Constraint* _20{};
    // static_param at offset 0x28
    const int* mTargetIdx_s{};
    // static_param at offset 0x30
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x38
    const float* mImpulse_s{};
    // static_param at offset 0x40
    const float* mMinLimit_s{};
    // static_param at offset 0x48
    const float* mMaxLimit_s{};
    // static_param at offset 0x50
    const float* mSwTh_s{};
    // static_param at offset 0x58
    const float* mFriction_s{};
    // static_param at offset 0x60
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x68
    sead::SafeString mOnASName_s{};
    // static_param at offset 0x78
    sead::SafeString mOffASName_s{};
    sead::Vector3f _88 = sead::Vector3f::zero;
    sead::Vector3f _94 = sead::Vector3f::zero;
    f32 _a0 = 0;
    ksys::act::Unk_7100d3bce4 _a8{mActor};
    void* _c0 = nullptr;
    u32 _c8 = 0;
    u32 _cc;
    f32 _d0 = 0;
    u32 _d4;
    ksys::phys::StaticCompoundRigidBodyGroup* _d8 = nullptr;
    u8 _e0 = 0;
};

}  // namespace uking::action
