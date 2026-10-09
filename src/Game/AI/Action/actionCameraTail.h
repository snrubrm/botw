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
    void sub_71007831EC();
    void sub_7100783380(f32 angle, bool move, sead::Vector3f* out);
    void sub_7100783CA4();
    void sub_7100783578();
    void sub_7100783688(bool chase);
    void sub_7100783A0C();
    void sub_71007840E0();
    // 0x71007837d8: whether the point at polar (r, a, b) from `base` is below the ground / water
    // height plus the camera's near radius.
    bool sub_71007837D8(const sead::Vector3f& base, f32 a, f32 b, f32 r);
    // 0x710078483c: the look-at position (camera _860._2b8 plus the OffsetY for the elevation).
    void sub_710078483C(sead::Vector3f* out);
    f32 sub_7100784288();
    void sub_710078441C();
    void sub_7100783BA8();
    bool sub_710078469C(f32* out);
    void sub_7100781F9C();
    void sub_71007821D0();
    // 0x7100784940 (placeholder name): the player's speed relative to the camera's target point (_164): 0 while
    // _12c < 20, else distance / frame delta, at most _124.
    f32 sub_7100784940();

    // 0x7100783380 passes this subobject at CameraTail + 0x4c to 0x7100784a20.
    struct PanState {
        struct Params {
            f32 speed;
            f32 direction;
            f32 radius;
            f32 angle;
            f32 follow_rate;
            f32 distance;
            f32 exponent;
            f32 damping;
        };
        void sub_7100784A20(const Params& params, sead::Vector3f* out);
        void sub_7100784D38(f32 speed, f32 direction);
        sead::Vector3f _0 = sead::Vector3f::zero;
        sead::Vector3f _c = sead::Vector3f::zero;
        sead::Vector3f _18 = sead::Vector3f::zero;
        sead::Vector3f _24 = {0.0f, 0.0f, 6.0f};
        f32 _30 = 1.0f;
        f32 _34 = 0.0f;
        f32 _38 = 0.0f;
        f32 _3c = 0.0f;
        f32 _40 = 2.0f;
        f32 _44 = 0.5f;
    };
    static_assert(sizeof(PanState) == 0x48);
    PanState mPan;
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
