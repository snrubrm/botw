#pragma once

#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::action {

class DgnObj_DLC_CogWheel_Rotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CogWheel_Rotate, ksys::act::ai::Action)
public:
    explicit DgnObj_DLC_CogWheel_Rotate(const InitArg& arg);
    ~DgnObj_DLC_CogWheel_Rotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const float* mTargetAngularDisplPerSec_s{};
    // dynamic_param at offset 0x28
    bool* mIsRegisteredFrame_d{};
    // map_unit_param at offset 0x30
    const float* mGearRatio_m{};
    // map_unit_param at offset 0x38
    const bool* mIsClockWiseRotation_m{};
    // aitree_variable at offset 0x40
    float* mRotationOffset_a{};
    s32 _48 = 0;
    f32 _4c = 0.0f;
    f32 _50 = 1.0f / 30.0f;
    f32 _54 = 1.0f;
    f32 _58 = 1.0f;
    f32 _5c = 0.0f;
    sead::Vector3f _60{0, 0, 0};
    // 0x6c / 0x7c: two quaternions (x, y, z, w; the body rotation and its conjugate), written as floats
    // because that reproduces most of the ctor's store merging.
    f32 _6c = 0.0f;
    f32 _70 = 0.0f;
    f32 _74 = 0.0f;
    f32 _78 = 1.0f;
    f32 _7c = 0.0f;
    f32 _80 = 0.0f;
    f32 _84 = 0.0f;
    f32 _88 = 1.0f;
    f32 _8c = 0.0f;
    u64 _90 = 0;
    f32 _98 = 1.0f;
    ksys::phys::MotionType _9c{-1};
    bool _a0 = false;
};
KSYS_CHECK_SIZE_NX150(DgnObj_DLC_CogWheel_Rotate, 0xa8);

}  // namespace uking::action
