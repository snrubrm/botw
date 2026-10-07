#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalk, CameraEvent)
public:
    explicit CameraEventTalk(const InitArg& arg);
    ~CameraEventTalk() override;

protected:
    int m38() override { return 0; }
    u64 m37() override { return 1; }
    void m43() override;
    void m46() override;

    u8 _4c[0xc];
    f32 _58 = 0;
    f32 _5c = angleStuff(0.0f);
    f32 _60 = angleStuff(0.0f);
    f32 _64 = 0;
    f32 _68 = 0;
    f32 _6c = 0;
    act::Unk_7102459dd8 _70;
    f32 _90 = 0;
    // static_param at offset 0x98
    const float* mDistanceMin_s{};
    // static_param at offset 0xa0
    const float* mDistanceMax_s{};
    // static_param at offset 0xa8
    const float* mRadiusNear_s{};
    // static_param at offset 0xb0
    const float* mRadiusFar_s{};
    // static_param at offset 0xb8
    const float* mLngNear_s{};
    // static_param at offset 0xc0
    const float* mLngFar_s{};
    // static_param at offset 0xc8
    const float* mLngRandom_s{};
    // static_param at offset 0xd0
    const float* mLatNear_s{};
    // static_param at offset 0xd8
    const float* mLatFar_s{};
    // static_param at offset 0xe0
    const float* mFovyNear_s{};
    // static_param at offset 0xe8
    const float* mFovyFar_s{};
    // static_param at offset 0xf0
    const float* mElevationAngleEffect_s{};
    // dynamic2_param at offset 0xf8
    float* mHeightOffset_d{};
    // static_param at offset 0x100
    const bool* mHideCheck_s{};
    // static_param at offset 0x108
    const bool* mLeftOnly_s{};
    // static_param at offset 0x110
    const bool* mRightOnly_s{};
    // dynamic2_param at offset 0x118
    bool* mNoConnect_d{};
    bool _120 = true;
};

}  // namespace uking::action
