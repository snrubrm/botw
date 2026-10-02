#include "Game/AI/Action/actionCameraEventPermitGfxNear.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraEventPermitGfxNear::CameraEventPermitGfxNear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool CameraEventPermitGfxNear::oneShot_() {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::Camera>(mActor))
            camera->_860._804.sub_710079AE20(0x1000);
    }
    return true;
}

}  // namespace uking::action
