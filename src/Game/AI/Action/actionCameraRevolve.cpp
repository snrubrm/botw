#include "Game/AI/Action/actionCameraRevolve.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraRevolve::CameraRevolve(const InitArg& arg) : CameraAction(arg) {}

CameraRevolve::~CameraRevolve() = default;

void CameraRevolve::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraRevolve::m36() {
    getStaticParam(&mLatTarget_s, "latTarget");
    getStaticParam(&mLatCus_s, "latCus");
    getStaticParam(&mIsKeepLat_s, "isKeepLat");
    getStaticParam(&mLngTarget_s, "lngTarget");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mIsKeepLng_s, "isKeepLng");
    getStaticParam(&mRadiusMin_s, "radiusMin");
    getStaticParam(&mRadiusMax_s, "radiusMax");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mSideOffset_s, "sideOffset");
    getStaticParam(&mSideOffsetCus_s, "sideOffsetCus");
    getStaticParam(&mWorldBaseOffset_s, "worldBaseOffset");
    getStaticParam(&mPlayerBaseOffset_s, "playerBaseOffset");
    getStaticParam(&mAtHCus_s, "atHCus");
    getStaticParam(&mAtHCusSword_s, "atHCusSword");
    getStaticParam(&mAtVCus_s, "atVCus");
    getStaticParam(&mFovy_s, "fovy");
    getStaticParam(&mFovyCus_s, "fovyCus");
    getStaticParam(&mStartCus_s, "startCus");
}

}  // namespace uking::action
