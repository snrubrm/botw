#include "Game/AI/Action/actionCameraEventTalkManualCtrl.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraEventTalkManualCtrl::CameraEventTalkManualCtrl(const InitArg& arg) : CameraEventTalkManualCtrlBase(arg) {}

void CameraEventTalkManualCtrl::m46() {
    CameraEventTalkManualCtrlBase::m46();
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mDistanceMax_s, "DistanceMax");
    getStaticParam(&mRadiusNear_s, "RadiusNear");
    getStaticParam(&mRadiusFar_s, "RadiusFar");
    getStaticParam(&mFovyNear_s, "FovyNear");
    getStaticParam(&mFovyFar_s, "FovyFar");
    getStaticParam(&mConnect_s, "Connect");
    getDynamicParam_2(&mNoConnect_d, "NoConnect");
}

f32 CameraEventTalkManualCtrl::m51() {
    return *mLatMin_s;
}

f32 CameraEventTalkManualCtrl::m52() {
    return *mLatMax_s;
}

f32 CameraEventTalkManualCtrl::m53() {
    return *mLatStickScale_s;
}

f32 CameraEventTalkManualCtrl::m54() {
    return *mLngStickScale_s;
}

f32 CameraEventTalkManualCtrl::m55() {
    return *mDistanceMin_s;
}

f32 CameraEventTalkManualCtrl::m56() {
    return *mDistanceMax_s;
}

f32 CameraEventTalkManualCtrl::m57() {
    return *mRadiusNear_s;
}

f32 CameraEventTalkManualCtrl::m58() {
    return *mRadiusFar_s;
}

f32 CameraEventTalkManualCtrl::m59() {
    return *mFovyNear_s;
}

f32 CameraEventTalkManualCtrl::m60() {
    return *mFovyFar_s;
}

f32 CameraEventTalkManualCtrl::m62() {
    return *mConnect_s;
}

bool CameraEventTalkManualCtrl::m63() {
    return *mNoConnect_d;
}

}  // namespace uking::action
