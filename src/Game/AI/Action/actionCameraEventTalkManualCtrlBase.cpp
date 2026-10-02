#include "Game/AI/Action/actionCameraEventTalkManualCtrlBase.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraEventTalkManualCtrlBase::CameraEventTalkManualCtrlBase(const InitArg& arg)
    : CameraEvent(arg) {}

void CameraEventTalkManualCtrlBase::m43() {
    _50.reset();
    _f4 |= 1;
    _f5 = 0;
    _ac = 0;
    getCamera();
}

void CameraEventTalkManualCtrlBase::m46() {
    getDynamicParam(&mHeightOffset_d, "HeightOffset");
}

void CameraEventTalkManualCtrlBase::m47(f32* elevation) {
    *elevation = angleStuff(0.0f);
    if (auto* camera = getCameraActor())
        *elevation = act::Unk_7100922700(camera->_860._0._0 - camera->_860._0._c)._4;
    *elevation = angleStuff(sead::Mathf::clamp(*elevation, _d8, _dc));
}

void CameraEventTalkManualCtrlBase::m48(f32* azimuth) {
    *azimuth = angleStuff(0.0f);
    if (auto* camera = getCameraActor())
        *azimuth = act::Unk_7100922700(camera->_860._0._0 - camera->_860._0._c)._8;
}

f32 CameraEventTalkManualCtrlBase::m51() {
    return -50.0f;
}

f32 CameraEventTalkManualCtrlBase::m52() {
    return 50.0f;
}

f32 CameraEventTalkManualCtrlBase::m53() {
    return 1.0f;
}

f32 CameraEventTalkManualCtrlBase::m54() {
    return 1.0f;
}

f32 CameraEventTalkManualCtrlBase::m55() {
    return 1.0f;
}

f32 CameraEventTalkManualCtrlBase::m56() {
    return 10.0f;
}

f32 CameraEventTalkManualCtrlBase::m57() {
    return 8.0f;
}

f32 CameraEventTalkManualCtrlBase::m58() {
    return 20.0f;
}

f32 CameraEventTalkManualCtrlBase::m59() {
    return 0.87f;
}

f32 CameraEventTalkManualCtrlBase::m60() {
    return 0.88f;
}

f32 CameraEventTalkManualCtrlBase::m61() {
    return -1.0f;
}

f32 CameraEventTalkManualCtrlBase::m62() {
    return 1.0f;
}

bool CameraEventTalkManualCtrlBase::m63() {
    return false;
}

}  // namespace uking::action
