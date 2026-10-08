#include "Game/AI/Action/actionCameraMagneCatch.h"

namespace uking::action {

CameraMagneCatch::CameraMagneCatch(const InitArg& arg) : CameraLockOnBase(arg) {}

CameraMagneCatch::~CameraMagneCatch() = default;

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

}  // namespace uking::action
