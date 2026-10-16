#include "Game/Actor/Behavior/behaviorSetMotionType.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

SetMotionType::SetMotionType(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetMotionType::~SetMotionType() = default;

bool SetMotionType::init_(sead::Heap* heap) {
    return true;
}

void SetMotionType::calc() {}

void SetMotionType::leave() {}

void SetMotionType::loadParams() {

}

void SetMotionType::enter() {
    if (auto* body = mActor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Fixed);
}

}  // namespace uking::behavior
