#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEvent.h"
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
