#include "Game/AI/Action/actionCameraEventTalk.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

CameraEventTalk::CameraEventTalk(const InitArg& arg) : CameraEvent(arg) {}

CameraEventTalk::~CameraEventTalk() = default;

void CameraEventTalk::m43() {
    if (getCamera()) {
        _6c = 1.0f;
        _70.sub_710079C384(20.0f, *mNoConnect_d ? 1.0f : 0.0f);
        _68 = sead::GlobalRandom::instance()->getF32() * *mLngRandom_s;
        _90 = 60.0f;
        _120 = true;
    }
}

void CameraEventTalk::m46() {
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mDistanceMax_s, "DistanceMax");
    getStaticParam(&mRadiusNear_s, "RadiusNear");
    getStaticParam(&mRadiusFar_s, "RadiusFar");
    getStaticParam(&mLngNear_s, "LngNear");
    getStaticParam(&mLngFar_s, "LngFar");
    getStaticParam(&mLngRandom_s, "LngRandom");
    getStaticParam(&mLatNear_s, "LatNear");
    getStaticParam(&mLatFar_s, "LatFar");
    getStaticParam(&mFovyNear_s, "FovyNear");
    getStaticParam(&mFovyFar_s, "FovyFar");
    getStaticParam(&mElevationAngleEffect_s, "ElevationAngleEffect");
    getDynamicParam_2(&mHeightOffset_d, "HeightOffset");
    getStaticParam(&mHideCheck_s, "HideCheck");
    getStaticParam(&mLeftOnly_s, "LeftOnly");
    getStaticParam(&mRightOnly_s, "RightOnly");
    getDynamicParam_2(&mNoConnect_d, "NoConnect");
}

}  // namespace uking::action
