#include "Game/AI/Action/actionCameraFinder.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraFinder::CameraFinder(const InitArg& arg) : CameraAction(arg) {}

CameraFinder::~CameraFinder() = default;

void CameraFinder::m33() {
    auto* camera = getCamera();
    if (!camera)
        return;

    _109 = camera->_860._800.sub_710079BFB0(0x100);
    if (camera->_860.sub_710079BDA4()) {
        _108 = true;
        sub_710076DEE0();
    } else {
        _108 = false;
        sub_710076E148();
    }
}

void CameraFinder::m36() {
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLatOffset_s, "LatOffset");
    getStaticParam(&mRadius_s, "radius");
    getStaticParam(&mOffsetY_s, "offsetY");
    getStaticParam(&mOffsetZ_s, "offsetZ");
    getStaticParam(&mAtCus_s, "atCus");
    getStaticParam(&mFovyMin_s, "fovyMin");
    getStaticParam(&mFovyMax_s, "fovyMax");
    getStaticParam(&mFovyCus_s, "fovyCus");
    getStaticParam(&mGyroScaleWithFovyMin_s, "GyroScaleWithFovyMin");
    getStaticParam(&mGyroScaleWithFovyMax_s, "GyroScaleWithFovyMax");
}

}  // namespace uking::action
