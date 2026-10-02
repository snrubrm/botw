#include "Game/AI/Action/actionCameraEventPlayerHideOff.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraEventPlayerHideOff::CameraEventPlayerHideOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool CameraEventPlayerHideOff::oneShot_() {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::Camera>(mActor))
            camera->_860._804.sub_710079AE20(0x400);
    }
    return true;
}

}  // namespace uking::action
