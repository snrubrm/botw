#include "Game/AI/Action/actionCameraEventReserveConnectTime.h"

namespace uking::action {

CameraEventReserveConnectTime::CameraEventReserveConnectTime(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_7102459708(this) {}

CameraEventReserveConnectTime::~CameraEventReserveConnectTime() = default;

bool CameraEventReserveConnectTime::oneShot_() {
    auto* camera = getCamera();
    if (!camera)
        return false;
    camera->_860.sub_710079BED0(*mInterpolateTime_d);
    return true;
}

void CameraEventReserveConnectTime::loadParams_() {
    getDynamicParam_2(&mInterpolateTime_d, "InterpolateTime");
}

}  // namespace uking::action
