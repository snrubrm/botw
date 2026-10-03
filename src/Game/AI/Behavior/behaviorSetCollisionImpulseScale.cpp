#include "Game/AI/Behavior/behaviorSetCollisionImpulseScale.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

SetCollisionImpulseScale::SetCollisionImpulseScale(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetCollisionImpulseScale::~SetCollisionImpulseScale() = default;

bool SetCollisionImpulseScale::m6(sead::Heap* heap) {
    return true;
}

void SetCollisionImpulseScale::m7() {}

void SetCollisionImpulseScale::m8() {
    if (auto* controller = mActor->getCharacterController()) {
        _30 = controller->sub_7100F62E5C();
        controller->sub_7100F62DD0(*mScale_s);
    }
}

void SetCollisionImpulseScale::m9() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62DD0(_30);
}

void SetCollisionImpulseScale::loadParams() {
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::behavior
