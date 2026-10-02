#include "Game/AI/Action/actionCameraWakeboard.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraWakeboard::CameraWakeboard(const InitArg& arg) : CameraAction(arg) {}

CameraWakeboard::~CameraWakeboard() = default;

void CameraWakeboard::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatLimitMin_s, "LatLimitMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatLimitMax_s, "LatLimitMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLngCus_s, "LngCus");
    getStaticParam(&mLngCusSpeedEffect_s, "LngCusSpeedEffect");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mRadiusMin_s, "RadiusMin");
    getStaticParam(&mRadiusMax_s, "RadiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetYBase_s, "OffsetYBase");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mOffsetZ_s, "OffsetZ");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mSideOffsetCus_s, "SideOffsetCus");
    getStaticParam(&mAtHCusNormal_s, "AtHCusNormal");
    getStaticParam(&mAtHCusSpurt_s, "AtHCusSpurt");
    getStaticParam(&mAtVCusMin_s, "AtVCusMin");
    getStaticParam(&mAtVCusMax_s, "AtVCusMax");
    getStaticParam(&mFovyNormal_s, "FovyNormal");
    getStaticParam(&mFovySpurt_s, "FovySpurt");
    getStaticParam(&mFovyCusAccel_s, "FovyCusAccel");
    getStaticParam(&mFovyCusDecel_s, "FovyCusDecel");
    getStaticParam(&mAutoModeConnect_s, "AutoModeConnect");
}

}  // namespace uking::action
