#include "Game/AI/Action/actionCameraEventTalkManualCtrlRet.h"
#include "Game/Actor/actCamera.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraEventTalkManualCtrlRet::CameraEventTalkManualCtrlRet(const InitArg& arg) : CameraEventTalkManualCtrlBase(arg) {}

void CameraEventTalkManualCtrlRet::m46() {
    CameraEventTalkManualCtrlBase::m46();
    getStaticParam(&mSavePoint_s, "SavePoint");
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
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mReturn_d, "Return");
    getDynamicParam_2(&mNoConnect_d, "NoConnect");
}

// NON_MATCHING: saved-state and scalar load scheduling differ.
void CameraEventTalkManualCtrlRet::m47(f32* elevation) {
    *elevation = angleStuff(0.0f);
    if (*mReturn_d) {
        if (auto* camera = getCameraActor()) {
            act::Unk_71009214b8 saved;
            if (camera->_860._72c._4.restore(&saved)) {
                const act::Unk_7100922700 polar(saved._0 - saved._c);
                *elevation = polar._4;
                *elevation = angleStuff(sead::Mathf::clamp(*elevation, _d8, _dc));
                return;
            }
        }
    }
    CameraEventTalkManualCtrlBase::m47(elevation);
}

void CameraEventTalkManualCtrlRet::m48(f32* azimuth) {
    *azimuth = angleStuff(0.0f);
    if (*mReturn_d) {
        if (auto* camera = getCameraActor()) {
            act::Unk_71009214b8 saved;
            if (camera->_860._72c._4.restore(&saved)) {
                const act::Unk_7100922700 polar(saved._0 - saved._c);
                *azimuth = polar._8;
                return;
            }
        }
    }
    CameraEventTalkManualCtrlBase::m48(azimuth);
}

void CameraEventTalkManualCtrlRet::m49() {
    _170 = *mSavePoint_s;
    if (!act::sub_710079BE9C(_170))
        _170 = 0;
}

bool CameraEventTalkManualCtrlRet::m50() {
    return m61() < _ac;
}

f32 CameraEventTalkManualCtrlRet::m51() {
    return *mLatMin_s;
}

f32 CameraEventTalkManualCtrlRet::m52() {
    return *mLatMax_s;
}

f32 CameraEventTalkManualCtrlRet::m53() {
    return *mLatStickScale_s;
}

f32 CameraEventTalkManualCtrlRet::m54() {
    return *mLngStickScale_s;
}

f32 CameraEventTalkManualCtrlRet::m55() {
    return *mDistanceMin_s;
}

f32 CameraEventTalkManualCtrlRet::m56() {
    return *mDistanceMax_s;
}

f32 CameraEventTalkManualCtrlRet::m57() {
    return *mRadiusNear_s;
}

f32 CameraEventTalkManualCtrlRet::m58() {
    return *mRadiusFar_s;
}

f32 CameraEventTalkManualCtrlRet::m59() {
    return *mFovyNear_s;
}

f32 CameraEventTalkManualCtrlRet::m60() {
    return *mFovyFar_s;
}

f32 CameraEventTalkManualCtrlRet::m61() {
    return *mCount_d;
}

f32 CameraEventTalkManualCtrlRet::m62() {
    return *mConnect_s;
}

bool CameraEventTalkManualCtrlRet::m63() {
    return *mNoConnect_d;
}

}  // namespace uking::action
