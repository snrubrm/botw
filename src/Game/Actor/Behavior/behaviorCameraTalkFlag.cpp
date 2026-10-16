#include "Game/Actor/Behavior/behaviorCameraTalkFlag.h"
#include "Game/Actor/actCamera.h"

namespace uking::behavior {

CameraTalkFlag::CameraTalkFlag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void CameraTalkFlag::enter() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* camera = sead::DynamicCast<uking::act::Camera>(actor))
        camera->_860._804.sub_710079AE20(0x20);
}

void CameraTalkFlag::leave() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* camera = sead::DynamicCast<uking::act::Camera>(actor))
        camera->_860._804.sub_710079AE40(0x20);
}

}  // namespace uking::behavior
