#include "Game/AI/Action/actionCameraWaterfallClimb.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraWaterfallClimb::CameraWaterfallClimb(const InitArg& arg) : CameraAction(arg) {}

CameraWaterfallClimb::~CameraWaterfallClimb() = default;

void CameraWaterfallClimb::m33() {
    _4c = 3;
    _10c = false;
    _94 = 0;
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraWaterfallClimb::m36() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLng_s, "Lng");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mHeightAllowance_s, "HeightAllowance");
    getStaticParam(&mManualHeightMin_s, "ManualHeightMin");
    getStaticParam(&mManualHeightMax_s, "ManualHeightMax");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
}

}  // namespace uking::action
