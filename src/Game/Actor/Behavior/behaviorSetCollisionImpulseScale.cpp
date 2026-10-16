#include "Game/Actor/Behavior/behaviorSetCollisionImpulseScale.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

SetCollisionImpulseScale::SetCollisionImpulseScale(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetCollisionImpulseScale::~SetCollisionImpulseScale() = default;

bool SetCollisionImpulseScale::init_(sead::Heap* heap) {
    return true;
}

void SetCollisionImpulseScale::calc() {}

void SetCollisionImpulseScale::enter() {
    if (auto* controller = mActor->getCharacterController()) {
        _30 = controller->sub_7100F62E5C();
        controller->sub_7100F62DD0(*mScale_s);
    }
}

void SetCollisionImpulseScale::leave() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62DD0(_30);
}

void SetCollisionImpulseScale::loadParams() {
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::behavior
