#include "Game/AI/Action/actionCameraHorseLockOnEmpty.h"

namespace uking::action {

CameraHorseLockOnEmpty::CameraHorseLockOnEmpty(const InitArg& arg) : CameraAction(arg) {}

CameraHorseLockOnEmpty::~CameraHorseLockOnEmpty() = default;

void CameraHorseLockOnEmpty::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraHorseLockOnEmpty::m36() {
    getStaticParam(&mLatSlow_s, "latSlow");
    getStaticParam(&mLatFast_s, "latFast");
    getStaticParam(&mLatControlRangeUp_s, "latControlRangeUp");
    getStaticParam(&mLatControlRangeDown_s, "latControlRangeDown");
    getStaticParam(&mLatCus_s, "latCus");
    getStaticParam(&mLngControlRange_s, "lngControlRange");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mRadiusSlow_s, "radiusSlow");
    getStaticParam(&mRadiusFast_s, "radiusFast");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mWorldBaseOffset_s, "worldBaseOffset");
    getStaticParam(&mPlayerBaseOffset_s, "playerBaseOffset");
    getStaticParam(&mAtHCus_s, "atHCus");
    getStaticParam(&mAtVCus_s, "atVCus");
    getStaticParam(&mFovySlow_s, "fovySlow");
    getStaticParam(&mFovyFast_s, "fovyFast");
    getStaticParam(&mFovyCus_s, "fovyCus");
    getStaticParam(&mStartCus_s, "startCus");
    getStaticParam(&mSpeedMin_s, "speedMin");
    getStaticParam(&mSpeedMax_s, "speedMax");
}

}  // namespace uking::action
