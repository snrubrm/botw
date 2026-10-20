#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/Camera/Action/actionCameraEvent.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys {
class Message;
}

namespace uking::action {

class CameraEventMove : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMove, CameraEvent)
public:
    explicit CameraEventMove(const InitArg& arg);
    ~CameraEventMove() override;

protected:
    void m43() override;
    void m44() override;
    void m45() override;
    void m46() override;
    bool handleMessage_(const ksys::Message* message) override;
    // 0x710075d338 / 0x710075d3cc (placeholder names): `link` becomes the player (acquired through an accessor) when
    // PlayerRelative is true / false, otherwise the event actor's link (or the speaker's if _2a3 is 0).
    void sub_710075D338(ksys::act::BaseProcLink* link);
    void sub_710075D3CC(ksys::act::BaseProcLink* link);
    // 0x710075e014 (placeholder name): interpolates the polar offset and the look-at point between the
    // event's current and target states by _1d8._18 and writes them to the camera.
    void sub_710075E014();
    // 0x710075d6d8 / 0x710075dcc4 (placeholder names): the two orbit-position updates called by m44
    // (the first follows the front bone matrix, the second applies the interpolated offset).
    void sub_710075D6D8();
    void sub_710075DCC4();
    // 0x710075e9b4 / 0x710075eb98 (placeholder names): tries up to `count` directions on a 2.5 degree
    // ring around `target` and on both sides of the elevation of `pos - target`, keeping the first
    // direction from `target` where `pos` is visible. `pos` receives the failing point; false means no
    // direction was found. The second form skips the elevation clamping of the offsets.
    bool sub_710075E810(const sead::Vector3f& pos, const sead::Vector3f& target);
    bool sub_710075E9B4(sead::Vector3f* pos, const sead::Vector3f& target, s32 count);
    bool sub_710075EB98(sead::Vector3f* pos, const sead::Vector3f& target, s32 count);

    uking::act::Unk_71009214b8 _4c;
    uking::act::Unk_71009214b8 _84;
    uking::act::Unk_71009214b8 _bc;
    ksys::act::BaseProcLink _f8;
    ksys::act::BaseProcLink _108;
    sead::Matrix34f _118 = sead::Matrix34f::ident;
    sead::Matrix34f _148 = sead::Matrix34f::ident;
    sead::Vector3f _178 = sead::Vector3f::zero;
    sead::Matrix34f _184 = sead::Matrix34f::ident;
    s32 _1b4 = 0;
    f32 _1b8 = 1.0f;
    uking::act::Unk_7100922700 _1bc;
    uking::act::Unk_7100922700 _1c8;
    f32 _1d4 = 0.0f;
    uking::act::Unk_7102459dd8 _1d8;
    // static_param at offset 0x1f8
    const int* mTargetActor_s{};
    // static_param at offset 0x200
    const int* mFrontBoneAxis_s{};
    // static_param at offset 0x208
    const int* mReviseModeRunning_s{};
    // static_param at offset 0x210
    const int* mReviseModeEnd_s{};
    // static_param at offset 0x218
    const float* mRadius_s{};
    // static_param at offset 0x220
    const float* mFovy_s{};
    // static_param at offset 0x228
    const bool* mFrontBoneAxisReverse_s{};
    // static_param at offset 0x230
    const bool* mCollisionInterpolateSkip_s{};
    // static_param at offset 0x238
    sead::SafeString mFrontBoneName_s{};
    // dynamic_param at offset 0x248
    float* mLat_d{};
    // dynamic_param at offset 0x250
    float* mLng_d{};
    // dynamic_param at offset 0x258
    float* mCount_d{};
    // dynamic_param at offset 0x260
    bool* mPlayerRelative_d{};
    // dynamic_param at offset 0x268
    bool* mStartCalcOnly_d{};
    // dynamic_param at offset 0x270
    bool* mUseImaginaryLineAngle_d{};
    // dynamic_param at offset 0x278
    bool* mCancelDrawOther_d{};
    // dynamic_param at offset 0x280
    bool* mLatReverse_d{};
    // dynamic_param at offset 0x288
    bool* mLngReverse_d{};
    // dynamic_param at offset 0x290
    bool* mNearSide_d{};
    // dynamic_param at offset 0x298
    sead::Vector3f* mOffset_d{};
    u8 _2a0 = 0;
    u8 _2a1 = 0;
    u8 _2a2 = 0;
    u8 _2a3 = 2;
    u8 _2a4 = 1;
    u8 _2a5 = 1;
};
KSYS_CHECK_SIZE_NX150(CameraEventMove, 0x2a8);

}  // namespace uking::action
