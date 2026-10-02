#include "Game/AI/Action/actionCameraEventLook.h"

namespace uking::action {

CameraEventLook::CameraEventLook(const InitArg& arg) : CameraEventLookBase(arg) {}

CameraEventLook::~CameraEventLook() = default;

void CameraEventLook::m46() {
    CameraEventLookBase::m46();
    getDynamicParam(&mTargetUniqueName_d, "TargetUniqueName");
}

}  // namespace uking::action
