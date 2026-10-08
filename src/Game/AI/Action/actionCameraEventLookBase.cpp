#include "Game/AI/Action/actionCameraEventLookBase.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraEventLookBase::CameraEventLookBase(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventLookBase::m46() {
    getDynamicParam_2(&mAngle_d, "Angle");
    getDynamicParam_2(&mNear_d, "Near");
    getDynamicParam_2(&mMiddle_d, "Middle");
    getDynamicParam_2(&mFar_d, "Far");
    getDynamicParam_2(&mLatMin_d, "LatMin");
    getDynamicParam_2(&mLatMax_d, "LatMax");
    getDynamicParam_2(&mFovyMin_d, "FovyMin");
    getDynamicParam_2(&mFovyMax_d, "FovyMax");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mLatMode_d, "LatMode");
    getDynamicParam_2(&mReviseMode_d, "ReviseMode");
    getDynamicParam_2(&mBaseAngleCamera_d, "BaseAngleCamera");
    getDynamicParam_2(&mBack_d, "Back");
    getDynamicParam_2(&mBgHitJump_d, "BgHitJump");
}

void CameraEventLookBase::m47() {}

void CameraEventLookBase::m48(sead::Matrix34f* mtx) {}

// NON_MATCHING: the original negates and selects the axis words in general registers (eor / csel w); ours mixes
// float and integer selects.
void CameraEventLookBase::sub_710075C7EC() {
    sead::Matrix34f mtx = sead::Matrix34f::zero;
    m48(&mtx);
    sead::Vector3f axis;
    mtx.getBase(axis, 2);
    const sead::Vector3f dir = *mBack_d ? -axis : axis;
    const f32 x = dir.x;
    const f32 y = dir.y;
    const f32 z = dir.z;
    _9c = angleStuff(0.0f);
    if (z != 0.0f || y != 0.0f || x != 0.0f)
        _9c = angleStuff(std::atan2(y, std::sqrt(x * x + z * z)));
    _9c = angleStuff(sead::Mathf::rad2deg(_9c));
}

}  // namespace uking::action
