#include "Game/AI/Behavior/behaviorCameraIndoorFlag.h"
#include "Game/Actor/actCamera.h"

namespace uking::behavior {

CameraIndoorFlag::CameraIndoorFlag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void CameraIndoorFlag::m8() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* camera = sead::DynamicCast<uking::act::Camera>(actor))
        camera->_860._804.sub_710079AE20(0x40);
}

void CameraIndoorFlag::m9() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* camera = sead::DynamicCast<uking::act::Camera>(actor))
        camera->_860._804.sub_710079AE40(0x40);
}

}  // namespace uking::behavior
