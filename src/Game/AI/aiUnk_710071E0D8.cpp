#include "Game/AI/aiUnk_710071E0D8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

void sub_710071E0D8(bool hover, ksys::act::Actor* actor) {
    const f32 gravity = hover ? 0.0f : 1.0f;
    if (auto* set = actor->getRigidBodyByName("Body")) {
        const int num_bodies = set->getRigidBodies().size();
        for (int i = 0; i < num_bodies; ++i)
            set->getRigidBody(i)->setGravityFactor(gravity);
    }
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5F458(hover ? ksys::act::MotionType::Hover : ksys::act::MotionType::_0);
        controller->sub_7100F5EEB8(gravity);
    }
}
