#include "Game/AI/Action/actionCameraEventOverwriteNear.h"

namespace uking::action {

CameraEventOverwriteNear::CameraEventOverwriteNear(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_7102459708(this) {}

CameraEventOverwriteNear::~CameraEventOverwriteNear() = default;

void CameraEventOverwriteNear::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* camera = getCamera())
        camera->_860.sub_710079ADD8(*mNear_d);
}

void CameraEventOverwriteNear::leave_() {
    if (auto* camera = getCamera())
        camera->_860.sub_710079AE30();
}

void CameraEventOverwriteNear::loadParams_() {
    getDynamicParam_2(&mNear_d, "Near");
}

}  // namespace uking::action
