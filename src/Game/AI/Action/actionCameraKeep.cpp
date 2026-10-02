#include "Game/AI/Action/actionCameraKeep.h"
#include <controller/seadController.h>
#include "Game/Actor/actCameraUtil.h"
#include "Game/gameMaskController.h"

namespace uking::action {

CameraKeep::CameraKeep(const InitArg& arg) : CameraAction(arg) {}

bool CameraKeep::isFinished() const {
    return sub_71007734CC() || ActionBase::isFinished();
}

void CameraKeep::m33() {
    if (auto* camera = getCamera())
        camera->_860._270.getTranslation(_4c);
}

void CameraKeep::m34() {
    if (!isFinished() && !isFailed() && sub_71007734CC())
        setFinished();
}

void CameraKeep::m41() {
    if (auto* camera = getCamera())
        camera->_860._817 = 0;
}

// NON_MATCHING: branch layout of the stick checks (the original sets w0 = 1 before the branches)
// and the final two loads are paired (ldp)
bool CameraKeep::sub_71007734CC() const {
    auto* camera = getCameraActor();
    if (!camera)
        return false;

    if ((_4c - camera->_860._270.getTranslation()).squaredLength() > 4.0f)
        return true;

    if (auto* controller = MaskController::getControllerSafe(MaskController::ControllerIdx::_1)) {
        if (controller->isHold(_58))
            return true;
        if (controller->getLeftStick().x != 0.0f || controller->getLeftStick().y != 0.0f)
            return true;
    }

    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    return stick.x != 0.0f || stick.y != 0.0f;
}

}  // namespace uking::action
