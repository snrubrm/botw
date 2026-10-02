#include "Game/AI/Action/actionEventSetFixed.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventSetFixed::EventSetFixed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetFixed::~EventSetFixed() = default;

bool EventSetFixed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetFixed::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

bool EventSetFixed::oneShot_() {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    auto* body = actor->getMainBody();
    if (controller) {
        controller->mFlags.set(0xc00);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        *mIsChangeToFixedInDemo_a = true;
    } else if (body && body->getMotionType() == ksys::phys::MotionType::Dynamic &&
               !body->hasFlag(ksys::phys::RigidBody::Flag::Fixed)) {
        body->setFixed(ksys::phys::Fixed(true), ksys::phys::PreserveVelocities(false));
        *mIsChangeToFixedInDemo_a = true;
    }
    return true;
}

}  // namespace uking::action
