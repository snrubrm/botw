#include "Game/AI/Action/actionCameraMotorcycle.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraMotorcycle::CameraMotorcycle(const InitArg& arg) : CameraAction(arg) {}

CameraMotorcycle::~CameraMotorcycle() = default;

void CameraMotorcycle::sub_710077A5A4(f32* out) {
    switch (_518) {
    case 0:
    case 2:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            *out = polar._8;
        }
        break;
    case 1:
    case 3:
        sub_710077AAD8(out);
        break;
    }
}

// NON_MATCHING: load order only (the original loads *mLatitudeMin_s before *out).
void CameraMotorcycle::sub_710077A648(f32* out) {
    switch (_518) {
    case 0:
    case 2:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            *out = polar._4;
        }
        break;
    case 1:
    case 3:
        *out = angleStuff(*mAutoLatitudeSlow_s + (*mAutoLatitudeFast_s - *mAutoLatitudeSlow_s) * _210);
        *out = angleStuff(*out + _270);
        break;
    }
    *out = angleStuff(sead::Mathf::clamp(*out, *mLatitudeMin_s, *mLatitudeMax_s));
}

// NON_MATCHING: the original merges the 0 and angle results through a general register (mov w8, wzr / fmov w8, s0 and one
// str w8); ours keeps the float registers.
void CameraMotorcycle::sub_710077AAD8(f32* out) {
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        const sead::Matrix34f& mtx = _51c == 1 ? _2e0 : _2b0;
        f32 angle;
        if (mtx.m[0][2] == -0.0f && mtx.m[2][2] == -0.0f)
            angle = 0.0f;
        else
            angle = angleStuff(sead::Mathf::rad2deg(std::atan2(-mtx.m[0][2], -mtx.m[2][2])));
        *out = angle;
    }
}

void CameraMotorcycle::m33() {
    _27c = 1;

    auto* camera = getCameraActor();
    if (camera && camera->_860._800.sub_710079BFB0(2) && camera->_860._7fc.sub_710079C0CC(2)) {
        _518 = 0;
    } else if (auto* c = getCameraActor()) {
        _518 = (c->_860._7f8.isOnBit(0)) + 1;
    } else {
        _518 = 1;
    }

    _310 = sead::Vector3f::zero;
    _31c = 0;
    _4f8 = *mCameraFollowPosCushionZNormal_s;
    _50c = 0;
    _510 = 0;
    _514 = 0;
    _508 = 0;
    _500 = 0;
}

void CameraMotorcycle::m36() {
    getStaticParam(&mSpeedMin_s, "SpeedMin");
    getStaticParam(&mSpeedMax_s, "SpeedMax");
    getStaticParam(&mLatitudeMin_s, "LatitudeMin");
    getStaticParam(&mLatitudeMax_s, "LatitudeMax");
    getStaticParam(&mAutoLatitudeSlow_s, "AutoLatitudeSlow");
    getStaticParam(&mAutoLatitudeFast_s, "AutoLatitudeFast");
    getStaticParam(&mAutoLatitudeB2ICushion_s, "AutoLatitudeB2ICushion");
    getStaticParam(&mCameraRadiusSlow_s, "CameraRadiusSlow");
    getStaticParam(&mCameraRadiusFast_s, "CameraRadiusFast");
    getStaticParam(&mCameraRadiusB2ICushion_s, "CameraRadiusB2ICushion");
    getStaticParam(&mSideOffsetSlow_s, "SideOffsetSlow");
    getStaticParam(&mSideOffsetFast_s, "SideOffsetFast");
    getStaticParam(&mMaxSideOffset_s, "MaxSideOffset");
    getStaticParam(&mSideOffsetCushion_s, "SideOffsetCushion");
    getStaticParam(&mVerticalOffsetSlow_s, "VerticalOffsetSlow");
    getStaticParam(&mVerticalOffsetFast_s, "VerticalOffsetFast");
    getStaticParam(&mVerticalOffetCushion_s, "VerticalOffetCushion");
    getStaticParam(&mAtBaseHCushion_s, "AtBaseHCushion");
    getStaticParam(&mAtBaseVCushion_s, "AtBaseVCushion");
    getStaticParam(&mFollowingRotateCushion_s, "FollowingRotateCushion");
    getStaticParam(&mFollowingTransCushion_s, "FollowingTransCushion");
    getStaticParam(&mFollowingAnglarVelCushion_s, "FollowingAnglarVelCushion");
    getStaticParam(&mAutoLngBaseCushion_s, "AutoLngBaseCushion");
    getStaticParam(&mAutoLngMaxRotSpeed_s, "AutoLngMaxRotSpeed");
    getStaticParam(&mAutoLngMaxRotSpeedSpin_s, "AutoLngMaxRotSpeedSpin");
    getStaticParam(&mSwitchingCushionRate_s, "SwitchingCushionRate");
    getStaticParam(&mAngularVelocityThreshold_s, "AngularVelocityThreshold");
    getStaticParam(&mCameraFollowRotCushion_s, "CameraFollowRotCushion");
    getStaticParam(&mCameraFollowPosCushionX_s, "CameraFollowPosCushionX");
    getStaticParam(&mCameraFollowPosCushionZNormal_s, "CameraFollowPosCushionZNormal");
    getStaticParam(&mCameraFollowPosCushionZStart_s, "CameraFollowPosCushionZStart");
    getStaticParam(&mCameraFollowPosCushionZWheelie_s, "CameraFollowPosCushionZWheelie");
    getStaticParam(&mCFPCZCushionUp_s, "CFPCZCushionUp");
    getStaticParam(&mCFPCZCushionDown_s, "CFPCZCushionDown");
    getStaticParam(&mCamFollowCusChangeTimeStart_s, "CamFollowCusChangeTimeStart");
    getStaticParam(&mCamFollowCusChangeTimeWheelie_s, "CamFollowCusChangeTimeWheelie");
    getStaticParam(&mFovySlow_s, "FovySlow");
    getStaticParam(&mFovyFast_s, "FovyFast");
    getStaticParam(&mFovyStart_s, "FovyStart");
    getStaticParam(&mFovyWheelie_s, "FovyWheelie");
    getStaticParam(&mFovyBaseCushionDown_s, "FovyBaseCushionDown");
    getStaticParam(&mFovyBaseCushionUpNormal_s, "FovyBaseCushionUpNormal");
    getStaticParam(&mFovyBaseCushionUpStart_s, "FovyBaseCushionUpStart");
    getStaticParam(&mFovyBaseCushionUpWheelie_s, "FovyBaseCushionUpWheelie");
    getStaticParam(&mFovyChangeTimeStart_s, "FovyChangeTimeStart");
    getStaticParam(&mFovyChangeTimeWheelie_s, "FovyChangeTimeWheelie");
    getStaticParam(&mIdealRotateVelScaleFactor_s, "IdealRotateVelScaleFactor");
    getStaticParam(&mAgainstIdealRotVelCushion_s, "AgainstIdealRotVelCushion");
    getStaticParam(&mSpeedRateCushion_s, "SpeedRateCushion");
    getStaticParam(&mSwitchingCushionRateLOE_s, "SwitchingCushionRateLOE");
    getStaticParam(&mSideOffsetByleaning_s, "SideOffsetByleaning");
    getStaticParam(&mThresholdAngleDiffCoeff_s, "ThresholdAngleDiffCoeff");
    getStaticParam(&mSpringBackToHardStartTime_s, "SpringBackToHardStartTime");
    getStaticParam(&mSpringBackToHardCushion_s, "SpringBackToHardCushion");
    getStaticParam(&mSpringChangeToSoftStartDistance_s, "SpringChangeToSoftStartDistance");
    getStaticParam(&mSpringChangeToSoftEndDistance_s, "SpringChangeToSoftEndDistance");
}

}  // namespace uking::action
