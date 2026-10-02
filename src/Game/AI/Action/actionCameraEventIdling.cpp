#include "Game/AI/Action/actionCameraEventIdling.h"

namespace uking::action {

CameraEventIdling::CameraEventIdling(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventIdling::m43() {
    setFinished();
}

// NON_MATCHING: the original tail-calls BaseProcLink::operator= and computes the destination first
// (C++14 operand order of an overloaded assignment)
void CameraEventIdling::m44() {
    if (auto* camera = getCamera()) {
        auto& data = camera->_860;
        data._818 = data._819;
        data._7c0[data._81a] = data._7c0[(data._81a + 1) % 2];
    }
}

}  // namespace uking::action
