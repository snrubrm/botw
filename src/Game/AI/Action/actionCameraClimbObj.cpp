#include "Game/AI/Action/actionCameraClimbObj.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraClimbObj::CameraClimbObj(const InitArg& arg) : CameraAction(arg) {}

CameraClimbObj::~CameraClimbObj() = default;

bool CameraClimbObj::m32(sead::Heap* heap) {
    return true;
}

void CameraClimbObj::m35() {
    if (auto* camera = getCamera())
        camera->_860._7fc.sub_710079B62C(0x200000);
}

}  // namespace uking::action
