#include "Game/AI/Behavior/behaviorSetMotionType.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

SetMotionType::SetMotionType(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetMotionType::~SetMotionType() = default;

bool SetMotionType::m6(sead::Heap* heap) {
    return true;
}

void SetMotionType::m7() {}

void SetMotionType::m9() {}

void SetMotionType::loadParams() {

}

void SetMotionType::m8() {
    if (auto* body = mActor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Fixed);
}

}  // namespace uking::behavior
