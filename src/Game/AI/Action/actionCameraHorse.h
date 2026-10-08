#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraHorse : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraHorse, CameraAction)
public:
    explicit CameraHorse(const InitArg& arg);
    ~CameraHorse() override;

protected:
    void m33() override;
    void m34() override;
    void m36() override;

    // 0x710076f638: clamps the "Cus" parameters into _238 - _25c.
    void sub_710076F638();
    // 0x7100771b94 (called by m34): eases _9c towards _84 and _a0 towards _88 (`_261` bit 2 selects the rate).
    void sub_7100771B94();
    // 0x71007710f8 (placeholder name): `*out` is the lerp of LatSlow / LatFast by _50 (wrapped), plus the
    // angle between the camera look-at point and the point polar(_0 - _c) from it (camera required).
    void sub_71007710F8(f32* out);
    // 0x71007711dc / 0x7100771684 (placeholder names): `*out` = the camera's elevation / azimuth, then the
    // right stick y / x scaled by the stick sensitivity and added to it (wrapped; camera required).
    void sub_71007711DC(f32* out);
    void sub_7100771684(f32* out);

    // Native state selection, transition and angle dispatch helpers.
    void sub_710077002C();
    void sub_71007701C4();
    void sub_71007702C8();
    void sub_710077071C();
    void sub_7100770474();
    void sub_7100770574();
    void sub_71007719C4();
    void sub_7100771C30(f32* out);
    void sub_7100771DA8(f32* out);
    void sub_710077066C(u8 previous_state);
    void sub_7100770B98();
    void sub_7100770DA8();
    void sub_7100771008(f32* out);
    void sub_71007712B0(f32* out);
    void sub_7100771480(f32* out);
    void sub_710077154C(f32* out);
    void sub_7100771758(f32* out);

    // A value that follows a parameter (m33 starts it from *startCus).
    struct Unk1 {
        f32 _0 = 0;
        f32 _4 = 0;
        f32 _8 = 0;
        u32 _c = 0;
        const float* _10 = nullptr;
    };

    f32 _4c = 0;
    f32 _50 = 0.5;
    f32 _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    f32 _60 = angleStuff(0);
    f32 _64 = angleStuff(0);
    f32 _68 = 0;
    sead::Vector3f _6c;  // transition start look-at position (0x7100770b98 / 0x7100770da8)
    sead::Vector3f _78 = sead::Vector3f::zero;
    f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 0;
    sead::Vector3f _90 = sead::Vector3f::zero;
    f32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
    f32 _a8 = 0;
    f32 _ac = 0;
    f32 _b0 = 0;
    f32 _b4 = 0;
    f32 _b8 = 0;
    f32 _bc = 0;
    sead::Vector3f _c0 = sead::Vector3f::zero;
    sead::Vector3f _cc = sead::Vector3f::zero;
    f32 _d8 = 0;
    f32 _dc = 0;
    Unk1 _e0;
    Unk1 _f8;
    act::Unk_7102459dd8 _110;
    f32 _130 = 0;
    f32 _134 = 0;
    f32 _138 = 0;
    f32 _13c = 0;
    f32 _140 = 0;
    // static_param at offset 0x148
    const float* mLatSlow_s{};
    // static_param at offset 0x150
    const float* mLatFast_s{};
    // static_param at offset 0x158
    const float* mLatCus_s{};
    // static_param at offset 0x160
    const float* mLatMin_s{};
    // static_param at offset 0x168
    const float* mLatMax_s{};
    // static_param at offset 0x170
    const float* mLngCusSlow_s{};
    // static_param at offset 0x178
    const float* mLngCusFast_s{};
    // static_param at offset 0x180
    const float* mLngCusParallel_s{};
    // static_param at offset 0x188
    const float* mLngCusVertical_s{};
    // static_param at offset 0x190
    const float* mRadiusSlow_s{};
    // static_param at offset 0x198
    const float* mRadiusFast_s{};
    // static_param at offset 0x1a0
    const float* mRadiusCus_s{};
    // static_param at offset 0x1a8
    const float* mSideOffsetSlow_s{};
    // static_param at offset 0x1b0
    const float* mSideOffsetFast_s{};
    // static_param at offset 0x1b8
    const float* mSideOffsetCus_s{};
    // static_param at offset 0x1c0
    const float* mOffsetYMin_s{};
    // static_param at offset 0x1c8
    const float* mOffsetYMax_s{};
    // static_param at offset 0x1d0
    const float* mAtHCusSlow_s{};
    // static_param at offset 0x1d8
    const float* mAtHCusFast_s{};
    // static_param at offset 0x1e0
    const float* mAtVCusSlow_s{};
    // static_param at offset 0x1e8
    const float* mAtVCusFast_s{};
    // static_param at offset 0x1f0
    const float* mFovySlow_s{};
    // static_param at offset 0x1f8
    const float* mFovyFast_s{};
    // static_param at offset 0x200
    const float* mFovyCus_s{};
    // static_param at offset 0x208
    const float* mStartCus_s{};
    // static_param at offset 0x210
    const float* mSpeedMin_s{};
    // static_param at offset 0x218
    const float* mSpeedMax_s{};
    // static_param at offset 0x220
    const float* mHandlingRateCoefficient_s{};
    // static_param at offset 0x228
    const float* mHandlingRateReturnSpeed_s{};
    // static_param at offset 0x230
    const float* mSideOffsetCusNoInput_s{};
    // the "Cus" parameters clamped to [0, 1] / >= 0 (sub_710076F638)
    f32 _238 = 0;
    f32 _23c = 0;
    f32 _240 = 0;
    f32 _244 = 0;
    f32 _248 = 0;
    f32 _24c = 0;
    f32 _250 = 0;
    f32 _254 = 0;
    f32 _258 = 1.0;
    f32 _25c = 0.01;
    sead::BitFlag8 _260;  // flags
    sead::BitFlag8 _261;
    u8 _262 = 0;  // previous _261 flag byte (copied by m34)
    u8 _263 = 4;
};
KSYS_CHECK_SIZE_NX150(CameraHorse, 0x268);

}  // namespace uking::action
