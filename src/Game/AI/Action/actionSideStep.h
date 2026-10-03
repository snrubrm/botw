#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include <math/seadMatrix.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideStep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SideStep, ksys::act::ai::Action)
public:
    explicit SideStep(const InitArg& arg);
    ~SideStep() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const float* mRotSpeedRatio_s{};
        // static_param at offset 0x28
        const float* mStopSpeedRatio_s{};
        // static_param at offset 0x30
        const float* mStopRotSpeedRatio_s{};
        // static_param at offset 0x38
        const float* mGravity_s{};
        // static_param at offset 0x40
        const float* mJumpHeight_s{};
        // dynamic_param at offset 0x48
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    ksys::VFRValue _50{0.0f};
    sead::Matrix33f _5c;
    Unk_7102451ba0 _80;
    sead::Vector3f _a8 = {0, 0, 0};
    sead::Vector3f _b4 = {0, 0, 0};
    sead::Vector3f _c0 = {0, 0, 0};
    f32 _cc = 0;
    f32 _d0 = 0;
    s8 _d4 = -1;
};

}  // namespace uking::action
