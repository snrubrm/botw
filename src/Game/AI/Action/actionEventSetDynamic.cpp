#include "Game/AI/Action/actionEventSetDynamic.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventSetDynamic::EventSetDynamic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetDynamic::~EventSetDynamic() = default;

bool EventSetDynamic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDynamic::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

bool EventSetDynamic::oneShot_() {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    auto* body = actor->getMainBody();
    if (*mIsChangeToFixedInDemo_a) {
        if (controller) {
            controller->mFlags.reset(0xc00);
        } else {
            if (!body)
                return true;
            body->setFixed(ksys::phys::Fixed(false), ksys::phys::PreserveVelocities(false));
        }
        *mIsChangeToFixedInDemo_a = false;
    }
    return true;
}

}  // namespace uking::action
