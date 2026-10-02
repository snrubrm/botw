#include "Game/AI/Action/actionCameraEvent.h"

namespace uking::action {

CameraEvent::CameraEvent(const InitArg& arg) : CameraAction(arg) {}

bool CameraEvent::m32(sead::Heap* heap) {
    return m42(heap);
}

void CameraEvent::m33() {
    if (auto* camera = getCamera())
        camera->sub_7100795C44();
    m43();
}

void CameraEvent::m34() {
    m44();
}

void CameraEvent::m35() {
    m45();
}

void CameraEvent::m36() {
    m46();
}

void CameraEvent::m41() {
    if (auto* camera = getCamera())
        camera->_860._817 = 0;
}

void CameraEvent::m43() {}

void CameraEvent::m44() {}

void CameraEvent::m45() {}

void CameraEvent::m46() {}

}  // namespace uking::action
