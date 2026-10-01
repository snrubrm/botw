#include "Game/AI/Action/actionCameraEventIdling.h"

namespace uking::action {

CameraEventIdling::CameraEventIdling(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventIdling::m43() {
    setFinished();
}

}  // namespace uking::action
