#include "Game/AI/Action/actionCameraLockOn.h"

namespace uking::action {

CameraLockOn::CameraLockOn(const InitArg& arg) : CameraLockOnBase(arg) {}

float CameraLockOn::m44() {
    return sub_71009222F4();
}

float CameraLockOn::m45() {
    return sub_7100922300();
}

}  // namespace uking::action
