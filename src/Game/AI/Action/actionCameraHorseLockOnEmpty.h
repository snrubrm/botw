#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraHorseLockOnEmpty : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraHorseLockOnEmpty, CameraAction)
public:
    explicit CameraHorseLockOnEmpty(const InitArg& arg);
    ~CameraHorseLockOnEmpty() override;

protected:
    void m35() override;
    void m36() override;

    f32 _4c = 0;
    f32 _50 = 0;
    f32 _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    f32 _60 = 0;
    f32 _64 = 0;
    f32 _68 = 0;
    f32 _6c = 0;
    // static_param at offset 0x70
    const float* mLatSlow_s{};
    // static_param at offset 0x78
    const float* mLatFast_s{};
    // static_param at offset 0x80
    const float* mLatControlRangeUp_s{};
    // static_param at offset 0x88
    const float* mLatControlRangeDown_s{};
    // static_param at offset 0x90
    const float* mLatCus_s{};
    // static_param at offset 0x98
    const float* mLngControlRange_s{};
    // static_param at offset 0xa0
    const float* mLngCus_s{};
    // static_param at offset 0xa8
    const float* mRadiusSlow_s{};
    // static_param at offset 0xb0
    const float* mRadiusFast_s{};
    // static_param at offset 0xb8
    const float* mRadiusCus_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mWorldBaseOffset_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mPlayerBaseOffset_s{};
    // static_param at offset 0xd0
    const float* mAtHCus_s{};
    // static_param at offset 0xd8
    const float* mAtVCus_s{};
    // static_param at offset 0xe0
    const float* mFovySlow_s{};
    // static_param at offset 0xe8
    const float* mFovyFast_s{};
    // static_param at offset 0xf0
    const float* mFovyCus_s{};
    // static_param at offset 0xf8
    const float* mStartCus_s{};
    // static_param at offset 0x100
    const float* mSpeedMin_s{};
    // static_param at offset 0x108
    const float* mSpeedMax_s{};
};
KSYS_CHECK_SIZE_NX150(CameraHorseLockOnEmpty, 0x110);

}  // namespace uking::action
