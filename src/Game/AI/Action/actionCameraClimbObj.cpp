#include "Game/AI/Action/actionCameraClimbObj.h"

namespace uking::action {

CameraClimbObj::CameraClimbObj(const InitArg& arg) : CameraAction(arg) {}

CameraClimbObj::~CameraClimbObj() = default;

bool CameraClimbObj::m32(sead::Heap* heap) {
    return true;
}

}  // namespace uking::action
