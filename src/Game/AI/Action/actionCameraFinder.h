#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraFinder : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraFinder, CameraAction)
public:
    explicit CameraFinder(const InitArg& arg);
    ~CameraFinder() override;

protected:
    void m33() override;
    // 0x710076e3a4 (not decompiled yet).
    void m34() override;

    // 0x710076dee0 / 0x710076e148 (not decompiled yet): called by m33 depending on
    // Unk_710079a8e8::sub_710079BDA4().
    void sub_710076DEE0();
    void sub_710076E148();
    void m36() override;

    f32 _4c = 0;
    f32 _50 = 0;
    f32 _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    u8 _60[0x78 - 0x60];
    f32 _78 = 0;
    f32 _7c = 0;
    f32 _80 = 0;
    act::Unk_7102459dd8 _88;
    // static_param at offset 0xa8
    const float* mLatMin_s{};
    // static_param at offset 0xb0
    const float* mLatMax_s{};
    // static_param at offset 0xb8
    const float* mLatOffset_s{};
    // static_param at offset 0xc0
    const float* mRadius_s{};
    // static_param at offset 0xc8
    const float* mOffsetY_s{};
    // static_param at offset 0xd0
    const float* mOffsetZ_s{};
    // static_param at offset 0xd8
    const float* mAtCus_s{};
    // static_param at offset 0xe0
    const float* mFovyMin_s{};
    // static_param at offset 0xe8
    const float* mFovyMax_s{};
    // static_param at offset 0xf0
    const float* mFovyCus_s{};
    // static_param at offset 0xf8
    const float* mGyroScaleWithFovyMin_s{};
    // static_param at offset 0x100
    const float* mGyroScaleWithFovyMax_s{};
    bool _108 = false;
    bool _109 = false;
};

}  // namespace uking::action
