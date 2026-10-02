#include "Game/AI/Action/actionCameraEventOverwriteFar.h"

namespace uking::action {

CameraEventOverwriteFar::CameraEventOverwriteFar(const InitArg& arg) : ksys::act::ai::Action(arg), Unk_7102459708(this) {}

CameraEventOverwriteFar::~CameraEventOverwriteFar() = default;

void CameraEventOverwriteFar::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* camera = getCamera())
        camera->_860.sub_710079AE88(*mFar_d);
}

void CameraEventOverwriteFar::leave_() {
    if (auto* camera = getCamera())
        camera->_860.sub_710079AED0();
}

void CameraEventOverwriteFar::loadParams_() {
    getDynamicParam_2(&mFar_d, "Far");
}

}  // namespace uking::action
