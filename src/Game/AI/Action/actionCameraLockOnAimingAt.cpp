#include "Game/AI/Action/actionCameraLockOnAimingAt.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraLockOnAimingAt::CameraLockOnAimingAt(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnAimingAt::~CameraLockOnAimingAt() = default;

void CameraLockOnAimingAt::m33() {
    _4c.sub_71008A4644();
    _128.reset();
    _138.set(0, 0, 0);
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraLockOnAimingAt::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mInputRangeNearDist_s, "InputRangeNearDist");
    getStaticParam(&mLatInputRange_s, "LatInputRange");
    getStaticParam(&mLngInputRange_s, "LngInputRange");
    getStaticParam(&mInputRangeFarDist_s, "InputRangeFarDist");
    getStaticParam(&mLatInputRangeFar_s, "LatInputRangeFar");
    getStaticParam(&mLngInputRangeFar_s, "LngInputRangeFar");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetX_s, "OffsetX");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mGyro_s, "Gyro");
}

}  // namespace uking::action
