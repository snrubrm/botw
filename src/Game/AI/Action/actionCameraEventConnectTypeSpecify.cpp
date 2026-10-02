#include "Game/AI/Action/actionCameraEventConnectTypeSpecify.h"
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraEventConnectTypeSpecify::CameraEventConnectTypeSpecify(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool CameraEventConnectTypeSpecify::oneShot_() {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::Camera>(mActor))
            camera->_860._804.sub_710079AE20(0x100000);
    }
    return true;
}

}  // namespace uking::action
