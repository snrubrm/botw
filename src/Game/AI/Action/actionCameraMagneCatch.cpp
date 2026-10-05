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

}  // namespace uking::action
