#include "Game/AI/Action/actionCameraEventLookBase.h"

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

}  // namespace uking::action
