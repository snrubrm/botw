#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraChase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraChase, CameraAction)
public:
    explicit CameraChase(const InitArg& arg);
    ~CameraChase() override;

protected:
    // 0x7100750858 / 0x71007518d8 (not decompiled yet).
    void m33() override;
    void m34() override;
    void m36() override;

    act::Unk_7102459dd8 _50;
    act::Unk_7102459dd8 _70;
    f32 _90 = 1.0;
    sead::Vector3f _94 = sead::Vector3f::zero;
    sead::Vector3f _a0 = sead::Vector3f::zero;
    sead::Vector3f _ac = sead::Vector3f::zero;
    sead::Vector3f _b8 = sead::Vector3f::zero;
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
    f32 _11c = 1.0;
    f32 _120 = 1.0;
    f32 _124 = 1.0;
    f32 _128 = 0;
    f32 _12c = 0;
    f32 _130 = 0;
    f32 _134 = 1.0;
    f32 _138 = 0;
    f32 _13c = 0;
    f32 _140 = 1.0;
    f32 _144 = 10.0;
    f32 _148 = 0;
    f32 _14c = 0;
    f32 _150 = 0;
    f32 _154 = 0;
    f32 _158 = 1.0;
    f32 _15c = 1.0;
    f32 _160 = 0;
    // static_param at offset 0x168
    const float* mLatMin_s{};
    // static_param at offset 0x170
    const float* mLatMax_s{};
    // static_param at offset 0x178
    const float* mLatLimitMin_s{};
    // static_param at offset 0x180
    const float* mLatLimitMax_s{};
    // static_param at offset 0x188
    const float* mLatMinWidth_s{};
    // static_param at offset 0x190
    const float* mLatMaxWidth_s{};
    // static_param at offset 0x198
    const float* mLatMinWeight_s{};
    // static_param at offset 0x1a0
    const float* mLatMaxWeight_s{};
    // static_param at offset 0x1a8
    const float* mLat_s{};
    // static_param at offset 0x1b0
    const float* mLngCus_s{};
    // static_param at offset 0x1b8
    const float* mLngCusSpeedEffect_s{};
    // static_param at offset 0x1c0
    const float* mLatStickScale_s{};
    // static_param at offset 0x1c8
    const float* mLngStickScale_s{};
    // static_param at offset 0x1d0
    const float* mRadiusMin_s{};
    // static_param at offset 0x1d8
    const float* mRadiusMax_s{};
    // static_param at offset 0x1e0
    const float* mRadiusMinWidth_s{};
    // static_param at offset 0x1e8
    const float* mRadiusMaxWidth_s{};
    // static_param at offset 0x1f0
    const float* mRadiusMinWeight_s{};
    // static_param at offset 0x1f8
    const float* mRadiusMaxWeight_s{};
    // static_param at offset 0x200
    const float* mRadius_s{};
    // static_param at offset 0x208
    const float* mAtMoveOffset_s{};
    // static_param at offset 0x210
    const float* mOffsetYMin_s{};
    // static_param at offset 0x218
    const float* mOffsetYMax_s{};
    // static_param at offset 0x220
    const float* mOffsetYMinWidth_s{};
    // static_param at offset 0x228
    const float* mOffsetYMaxWidth_s{};
    // static_param at offset 0x230
    const float* mOffsetYMinWeight_s{};
    // static_param at offset 0x238
    const float* mOffsetYMaxWeight_s{};
    // static_param at offset 0x240
    const float* mAtHCusMin_s{};
    // static_param at offset 0x248
    const float* mAtHCusMax_s{};
    // static_param at offset 0x250
    const float* mAtVCusMin_s{};
    // static_param at offset 0x258
    const float* mAtVCusMax_s{};
    // static_param at offset 0x260
    const float* mFovy_s{};
    // static_param at offset 0x268
    const float* mConnect_s{};
    // static_param at offset 0x270
    const float* mConnectItem_s{};
    // static_param at offset 0x278
    const float* mConnectIndoor_s{};
    // static_param at offset 0x280
    const bool* mBgCheckToAt_s{};
    // static_param at offset 0x288
    const int* mProcMode_s{};
    // static_param at offset 0x290
    const int* mControlMode_s{};
    // static_param at offset 0x298
    const bool* mKeepManual_s{};
    u8 _2a0[0x2ba - 0x2a0]{};
    u8 _2ba = 2;
    u8 _2bb = 5;
    u8 _2bc = 5;
    u8 _2bd = 3;
    bool _2be = false;
};
KSYS_CHECK_SIZE_NX150(CameraChase, 0x2c0);

}  // namespace uking::action
