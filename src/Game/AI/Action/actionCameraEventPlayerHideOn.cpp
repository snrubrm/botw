#include "Game/AI/Action/actionCameraEventPlayerHideOn.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraEventPlayerHideOn::CameraEventPlayerHideOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool CameraEventPlayerHideOn::oneShot_() {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::Camera>(mActor))
            camera->_860._804.sub_710079AE40(0x400);
    }
    return true;
}

}  // namespace uking::action
