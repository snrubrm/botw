#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWakeboard : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWakeboard, CameraAction)
public:
    explicit CameraWakeboard(const InitArg& arg);
    ~CameraWakeboard() override;

protected:
    // m33 / m34 (not decompiled yet).
    void m33() override;
    void m34() override;
    void m36() override;

    act::Unk_7102459dd8 _50;
    act::Unk_7102459dd8 _70;
    f32 _90 = 1.0;
    sead::Vector3f _94 = sead::Vector3f::zero;
    sead::Vector3f _a0 = sead::Vector3f::zero;
    sead::Vector3f _ac = sead::Vector3f::zero;
    f32 _b8 = 0;
    f32 _bc = 0;
    f32 _c0 = 0;
    f32 _c4 = 0;
    f32 _c8 = 0;
    f32 _cc = 0;
    f32 _d0 = 0;
    f32 _d4 = 0;
    f32 _d8 = 0;
    f32 _dc = 0;
    f32 _e0 = 0;
    f32 _e4 = 0;
    f32 _e8 = 0;
    f32 _ec = 0;
    f32 _f0 = 0;
    f32 _f4 = 0;
    f32 _f8 = 0;
    f32 _fc = 0;
    f32 _100 = 0;
    f32 _104 = 0;
    f32 _108 = 0;
    f32 _10c = 0;
    f32 _110 = 0;
    f32 _114 = 0;
    f32 _118 = 0;
    // static_param at offset 0x120
    const float* mLatMin_s{};
    // static_param at offset 0x128
    const float* mLatLimitMin_s{};
    // static_param at offset 0x130
    const float* mLatMax_s{};
    // static_param at offset 0x138
    const float* mLatLimitMax_s{};
    // static_param at offset 0x140
    const float* mLatMinWidth_s{};
    // static_param at offset 0x148
    const float* mLatMaxWidth_s{};
    // static_param at offset 0x150
    const float* mLatMinWeight_s{};
    // static_param at offset 0x158
    const float* mLatMaxWeight_s{};
    // static_param at offset 0x160
    const float* mLat_s{};
    // static_param at offset 0x168
    const float* mLngCus_s{};
    // static_param at offset 0x170
    const float* mLngCusSpeedEffect_s{};
    // static_param at offset 0x178
    const float* mLatStickScale_s{};
    // static_param at offset 0x180
    const float* mLngStickScale_s{};
    // static_param at offset 0x188
    const float* mRadiusMin_s{};
    // static_param at offset 0x190
    const float* mRadiusMax_s{};
    // static_param at offset 0x198
    const float* mRadiusMinWidth_s{};
    // static_param at offset 0x1a0
    const float* mRadiusMaxWidth_s{};
    // static_param at offset 0x1a8
    const float* mRadiusMinWeight_s{};
    // static_param at offset 0x1b0
    const float* mRadiusMaxWeight_s{};
    // static_param at offset 0x1b8
    const float* mRadius_s{};
    // static_param at offset 0x1c0
    const float* mOffsetYBase_s{};
    // static_param at offset 0x1c8
    const float* mOffsetYMin_s{};
    // static_param at offset 0x1d0
    const float* mOffsetYMax_s{};
    // static_param at offset 0x1d8
    const float* mOffsetYMinWidth_s{};
    // static_param at offset 0x1e0
    const float* mOffsetYMaxWidth_s{};
    // static_param at offset 0x1e8
    const float* mOffsetYMinWeight_s{};
    // static_param at offset 0x1f0
    const float* mOffsetYMaxWeight_s{};
    // static_param at offset 0x1f8
    const float* mOffsetZ_s{};
    // static_param at offset 0x200
    const float* mSideOffset_s{};
    // static_param at offset 0x208
    const float* mSideOffsetCus_s{};
    // static_param at offset 0x210
    const float* mAtHCusNormal_s{};
    // static_param at offset 0x218
    const float* mAtHCusSpurt_s{};
    // static_param at offset 0x220
    const float* mAtVCusMin_s{};
    // static_param at offset 0x228
    const float* mAtVCusMax_s{};
    // static_param at offset 0x230
    const float* mFovyNormal_s{};
    // static_param at offset 0x238
    const float* mFovySpurt_s{};
    // static_param at offset 0x240
    const float* mFovyCusAccel_s{};
    // static_param at offset 0x248
    const float* mFovyCusDecel_s{};
    // static_param at offset 0x250
    const float* mAutoModeConnect_s{};
    u8 _258[0x2c2 - 0x258]{};
    u8 _2c2 = 5;
};

}  // namespace uking::action
