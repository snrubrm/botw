#include "Game/AI/Action/actionCameraMagneCatch.h"

#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraMagneCatch::CameraMagneCatch(const InitArg& arg) : CameraLockOnBase(arg) {}

CameraMagneCatch::~CameraMagneCatch() = default;

void CameraMagneCatch::m43() {
    _454 = 0.0f;
}

bool CameraMagneCatch::m51() {
    auto* camera = getCamera();
    if (!camera)
        return false;
    _64 = camera->_860._4cc;
    _70 = camera->_860._4cc;
    _7c = camera->_860._4cc;
    return true;
}

void CameraMagneCatch::sub_7100775B78(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 1.0f);
}

void CameraMagneCatch::sub_7100775B80(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 0.5f);
}

void CameraMagneCatch::sub_7100775B88(act::Unk_71009214b8* out) {
    sub_7100775F84(out, 0.0f);
}

float CameraMagneCatch::m44() {
    return sub_7100922318();
}

float CameraMagneCatch::m45() {
    return sub_7100922324();
}

bool CameraMagneCatch::m55(f32* out0, f32* out1) {
    *out0 = 1.0f;
    *out1 = 0.0f;
    if (!sub_7100786CC0())
        return false;
    f32 value = 1.0f;
    if (_f4 == 1)
        value = 0.5f;
    if (_f4 == 2)
        value = 0.0f;
    *out0 = value;
    *out1 = 0.0f;
    return true;
}

// NON_MATCHING: float stack slots and paired zero stores differ.
void CameraMagneCatch::sub_7100775F84(act::Unk_71009214b8* out, f32 rate) {
    auto* camera = getCamera();
    if (!camera)
        return;
    *out = camera->_860._0;
    f32 longitude = 0.0f;
    sub_7100786974(&longitude);
    longitude = angleStuff(longitude + sub_7100922530(_a0._14));
    const f32 current = angleStuff(-_88._10);
    f32 latitude = *mLatOffsetNear_s + (*mLatOffsetFar_s - *mLatOffsetNear_s) * _b8;
    if (angleStuff(current) > angleStuff(latitude))
        latitude += angleStuff(current - latitude);
    angleStuff(latitude);
    latitude = angleStuff(current + angleStuff(angleStuff(latitude) - current) * rate);
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    if (latitude < min)
        latitude = min;
    else if (!(latitude <= max))
        latitude = max;
    const f32 clamped_latitude = angleStuff(latitude);
    sub_7100786A44(out, &clamped_latitude, &longitude);
}

}  // namespace uking::action
