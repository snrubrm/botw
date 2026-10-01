#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"
#include <math/seadMatrix.h>

namespace uking::action {

class JumpTo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpTo, ksys::act::ai::Action)
public:
    explicit JumpTo(const InitArg& arg);
    ~JumpTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32() = 0;
    virtual void m33() = 0;
    virtual void m34() = 0;
    virtual bool m35();
    virtual bool m36();
    virtual bool m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual const sead::Vector3f& m44();

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mJumpHeight_s{};
    // static_param at offset 0x30
    const float* mJumpGravity_s{};
    // static_param at offset 0x38
    const float* mPosReduceRatioOnGround_s{};
    // static_param at offset 0x40
    const float* mRotReduceRatioOnGround_s{};
    // static_param at offset 0x48
    const float* mInWaterDepth_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _58{0.0f};
    sead::Matrix33f _64;
    sead::Vector3f _88{0.0f, 0.0f, 0.0f};
    float _94 = 0.0f;
    int _98 = -1;
};

}  // namespace uking::action
