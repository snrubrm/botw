#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraTail : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraTail, CameraAction)
public:
    explicit CameraTail(const InitArg& arg);
    ~CameraTail() override;

protected:
    bool m32(sead::Heap* heap) override;
    void m33() override;
    void m34() override;
    void m36() override;

    // 0x71007830fc: smooths _134 towards the player's rotation.
    void sub_71007830FC();
    // 0x71007837d8: whether the point at polar (r, a, b) from `base` is below the ground / water
    // height plus the camera's near radius.
    bool sub_71007837D8(const sead::Vector3f& base, f32 a, f32 b, f32 r);
    // 0x710078483c: the look-at position (camera _860._2b8 plus the OffsetY for the elevation).
    void sub_710078483C(sead::Vector3f* out);
    // 0x7100784940 (placeholder name): the player's speed relative to the camera's target point (_164): 0 while
    // _12c < 20, else distance / frame delta, at most _124.
    f32 sub_7100784940();

    sead::Vector3f _4c = sead::Vector3f::zero;
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    sead::Vector3f _70 = {0, 0, 6.0};
    f32 _7c = 1.0;
    f32 _80 = 0;
    f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 2.0;
    f32 _90 = 0.5;
    f32 _94 = 0;
    sead::Vector3f _98 = sead::Vector3f::zero;
    sead::Vector3f _a4 = sead::Vector3f::zero;
    f32 _b0{};
    f32 _b4{};
    f32 _b8{};
    f32 _bc{};
    f32 _c0{};
    f32 _c4{};
    f32 _c8{};
    f32 _cc{};
    f32 _d0{};
    f32 _d4{};
    f32 _d8{};
    f32 _dc{};
    f32 _e0{};
    f32 _e4{};
    f32 _e8{};
    f32 _ec{};
    f32 _f0{};
    f32 _f4{};
    act::Unk_7102459dd8 _f8;
    f32 _118 = 1.0;
    f32 _11c = 1.0;
    f32 _120 = 0;
    f32 _124 = 0;
    f32 _128 = 0;
    f32 _12c = 0;
    f32 _130 = 0;
    sead::Matrix33f _134 = sead::Matrix33f::ident;
    f32 _158 = angleStuff(0);
    f32 _15c;
    // static_param at offset 0x160
    const float* mLatMin_s{};
    // static_param at offset 0x168
    const float* mLatMax_s{};
    // static_param at offset 0x170
    const float* mRadius_s{};
    // static_param at offset 0x178
    const float* mRadiusDolly_s{};
    // static_param at offset 0x180
    const float* mOffsetYMin_s{};
    // static_param at offset 0x188
    const float* mOffsetYMax_s{};
    // static_param at offset 0x190
    const float* mFovy_s{};
    // static_param at offset 0x198
    const float* mDstAngle_s{};
    // static_param at offset 0x1a0
    const float* mPanSpeedParam_s{};
    void* _1a8{};
    // static_param at offset 0x1b0
    const float* mStartInterpolateParam_s{};
    // static_param at offset 0x1b8
    const float* mResetInterpolateParam_s{};
    // static_param at offset 0x1c0
    const float* mTargetSpeedMax_s{};
    f32 _1c8 = 1.0;
    u8 _1cc = 0;
    u8 _1cd = 2;
};
KSYS_CHECK_SIZE_NX150(CameraTail, 0x1d0);

}  // namespace uking::action
