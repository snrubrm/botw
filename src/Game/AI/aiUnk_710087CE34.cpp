#include "Game/AI/aiUnk_710087CE34.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

void sub_710087CE34(ksys::act::Actor* actor) {
    if (auto* controller = actor->getCharacterController()) {
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityTree);
    }
}

void sub_710087CE90(ksys::act::Actor* actor) {
    if (auto* controller = actor->getCharacterController()) {
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityTree);
    }
}

void sub_7100873264(ksys::act::Actor* actor) {
    if (auto* body_set = actor->getPhysics()->findBodyByName(*sub_71007A24D0())) {
        if (auto* body = body_set->findBodyByHavokName("Head"))
            body->addToWorld();
    }
}

void sub_71008732C8(ksys::act::Actor* actor) {
    if (auto* body_set = actor->getPhysics()->findBodyByName(*sub_71007A24D0())) {
        if (auto* body = body_set->findBodyByHavokName("Head"))
            body->removeFromWorld();
    }
}
