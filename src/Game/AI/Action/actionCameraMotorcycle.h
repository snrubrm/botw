#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycle : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycle, CameraAction)
public:
    explicit CameraMotorcycle(const InitArg& arg);
    ~CameraMotorcycle() override;

protected:
    void m33() override;
    void m36() override;

    // 0x710077a5a4 / 0x710077a648 / 0x710077aad8 (placeholder names): write the longitude / latitude / follow
    // angle for the current mode (_518) to `out`.
    void sub_710077A5A4(f32* out);
    void sub_710077A648(f32* out);
    void sub_710077AAD8(f32* out);

    // static_param at offset 0x50
    const float* mSpeedMin_s{};
    // static_param at offset 0x58
    const float* mSpeedMax_s{};
    // static_param at offset 0x60
    const float* mLatitudeMin_s{};
    // static_param at offset 0x68
    const float* mLatitudeMax_s{};
    // static_param at offset 0x70
    const float* mAutoLatitudeSlow_s{};
    // static_param at offset 0x78
    const float* mAutoLatitudeFast_s{};
    // static_param at offset 0x80
    const float* mAutoLatitudeB2ICushion_s{};
    // static_param at offset 0x88
    const float* mCameraRadiusSlow_s{};
    // static_param at offset 0x90
    const float* mCameraRadiusFast_s{};
    // static_param at offset 0x98
    const float* mCameraRadiusB2ICushion_s{};
    // static_param at offset 0xa0
    const float* mSideOffsetSlow_s{};
    // static_param at offset 0xa8
    const float* mSideOffsetFast_s{};
    // static_param at offset 0xb0
    const float* mMaxSideOffset_s{};
    // static_param at offset 0xb8
    const float* mSideOffsetCushion_s{};
    // static_param at offset 0xc0
    const float* mVerticalOffsetSlow_s{};
    // static_param at offset 0xc8
    const float* mVerticalOffsetFast_s{};
    // static_param at offset 0xd0
    const float* mVerticalOffetCushion_s{};
    // static_param at offset 0xd8
    const float* mAtBaseHCushion_s{};
    // static_param at offset 0xe0
    const float* mAtBaseVCushion_s{};
    // static_param at offset 0xe8
    const float* mFollowingRotateCushion_s{};
    // static_param at offset 0xf0
    const float* mFollowingTransCushion_s{};
    // static_param at offset 0xf8
    const float* mFollowingAnglarVelCushion_s{};
    // static_param at offset 0x100
    const float* mAutoLngBaseCushion_s{};
    // static_param at offset 0x108
    const float* mAutoLngMaxRotSpeed_s{};
    // static_param at offset 0x110
    const float* mAutoLngMaxRotSpeedSpin_s{};
    // static_param at offset 0x118
    const float* mSwitchingCushionRate_s{};
    // static_param at offset 0x120
    const float* mAngularVelocityThreshold_s{};
    // static_param at offset 0x128
    const float* mCameraFollowRotCushion_s{};
    // static_param at offset 0x130
    const float* mCameraFollowPosCushionX_s{};
    // static_param at offset 0x138
    const float* mCameraFollowPosCushionZNormal_s{};
    // static_param at offset 0x140
    const float* mCameraFollowPosCushionZStart_s{};
    // static_param at offset 0x148
    const float* mCameraFollowPosCushionZWheelie_s{};
    // static_param at offset 0x150
    const float* mCFPCZCushionUp_s{};
    // static_param at offset 0x158
    const float* mCFPCZCushionDown_s{};
    // static_param at offset 0x160
    const float* mCamFollowCusChangeTimeStart_s{};
    // static_param at offset 0x168
    const float* mCamFollowCusChangeTimeWheelie_s{};
    // static_param at offset 0x170
    const float* mFovySlow_s{};
    // static_param at offset 0x178
    const float* mFovyFast_s{};
    // static_param at offset 0x180
    const float* mFovyStart_s{};
    // static_param at offset 0x188
    const float* mFovyWheelie_s{};
    // static_param at offset 0x190
    const float* mFovyBaseCushionDown_s{};
    // static_param at offset 0x198
    const float* mFovyBaseCushionUpNormal_s{};
    // static_param at offset 0x1a0
    const float* mFovyBaseCushionUpStart_s{};
    // static_param at offset 0x1a8
    const float* mFovyBaseCushionUpWheelie_s{};
    // static_param at offset 0x1b0
    const float* mFovyChangeTimeStart_s{};
    // static_param at offset 0x1b8
    const float* mFovyChangeTimeWheelie_s{};
    // static_param at offset 0x1c0
    const float* mIdealRotateVelScaleFactor_s{};
    // static_param at offset 0x1c8
    const float* mAgainstIdealRotVelCushion_s{};
    // static_param at offset 0x1d0
    const float* mSpeedRateCushion_s{};
    // static_param at offset 0x1d8
    const float* mSwitchingCushionRateLOE_s{};
    // static_param at offset 0x1e0
    const float* mSideOffsetByleaning_s{};
    // static_param at offset 0x1e8
    const float* mThresholdAngleDiffCoeff_s{};
    // static_param at offset 0x1f0
    const float* mSpringBackToHardStartTime_s{};
    // static_param at offset 0x1f8
    const float* mSpringBackToHardCushion_s{};
    // static_param at offset 0x200
    const float* mSpringChangeToSoftStartDistance_s{};
    // static_param at offset 0x208
    const float* mSpringChangeToSoftEndDistance_s{};
    // Members not recovered yet (class size from the factory).
    f32 _210;
    u8 _214[0x270 - 0x214];
    f32 _270;
    u8 _274[0x27c - 0x274];
    u8 _27c;
    u8 _27d[0x2b0 - 0x27d];
    sead::Matrix34f _2b0;
    sead::Matrix34f _2e0;
    sead::Vector3f _310;
    u32 _31c;
    u8 _320[0x4f8 - 0x320];
    f32 _4f8;
    u64 _500;
    u8 _508;
    u8 _509[0x50c - 0x509];
    u32 _50c;
    u8 _510;
    u8 _511[0x514 - 0x511];
    u32 _514;
    u8 _518;
    u8 _519[0x51c - 0x519];
    u32 _51c;
    u8 _520[0x528 - 0x520];
};
KSYS_CHECK_SIZE_NX150(CameraMotorcycle, 0x528);

}  // namespace uking::action
