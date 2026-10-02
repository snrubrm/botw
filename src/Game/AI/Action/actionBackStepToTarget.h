#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionActionEx.h"
#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStepToTarget : public ActionEx {
    SEAD_RTTI_OVERRIDE(BackStepToTarget, ActionEx)
public:
    explicit BackStepToTarget(const InitArg& arg);
    ~BackStepToTarget() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33(sead::Vector3f* dir, const sead::Vector3f& up);
    virtual void m34() = 0;
    virtual void m35() = 0;
    virtual void m36() = 0;
    virtual void m37() = 0;
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41(f32* a, sead::Vector3f* b) = 0;
    virtual f32 m42();

    // static_param at offset 0x20
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x28
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mJumpGravity_s{};
    // static_param at offset 0x38
    const float* mJumpHeight_s{};
    // static_param at offset 0x40
    const float* mRotRatio_s{};
    // static_param at offset 0x48
    const bool* mCheckRotEvent_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    f32 _58 = 0;
    sead::Matrix33f _5c;
    Unk_7102451ba0 _80;
    sead::Vector3f _a8 = {0, 0, 0};
    f32 _b4 = 0;
    f32 _b8 = 0;
    s8 _bc = -1;
};

}  // namespace uking::action
