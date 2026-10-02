#include "Game/AI/Action/actionCameraChase.h"

namespace uking::action {

CameraChase::CameraChase(const InitArg& arg) : CameraAction(arg) {}

CameraChase::~CameraChase() = default;

void CameraChase::m36() {
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLatLimitMin_s, "LatLimitMin");
    getStaticParam(&mLatLimitMax_s, "LatLimitMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLat_s, "lat");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mLngCusSpeedEffect_s, "lngCusSpeedEffect");
    getStaticParam(&mLatStickScale_s, "latStickScale");
    getStaticParam(&mLngStickScale_s, "lngStickScale");
    getStaticParam(&mRadiusMin_s, "radiusMin");
    getStaticParam(&mRadiusMax_s, "radiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mRadius_s, "radius");
    getStaticParam(&mAtMoveOffset_s, "atMoveOffset");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mAtHCusMin_s, "AtHCusMin");
    getStaticParam(&mAtHCusMax_s, "AtHCusMax");
    getStaticParam(&mAtVCusMin_s, "atVCusMin");
    getStaticParam(&mAtVCusMax_s, "atVCusMax");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mConnect_s, "Connect");
    getStaticParam(&mConnectItem_s, "ConnectItem");
    getStaticParam(&mConnectIndoor_s, "ConnectIndoor");
    getStaticParam(&mProcMode_s, "ProcMode");
    getStaticParam(&mControlMode_s, "controlMode");
    getStaticParam(&mBgCheckToAt_s, "BgCheckToAt");
    getStaticParam(&mKeepManual_s, "keepManual");
}

}  // namespace uking::action
