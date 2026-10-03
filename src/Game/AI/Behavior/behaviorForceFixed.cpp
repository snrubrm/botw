#include "Game/AI/Behavior/behaviorForceFixed.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

ForceFixed::ForceFixed(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceFixed::~ForceFixed() = default;

bool ForceFixed::m6(sead::Heap* heap) {
    return true;
}

void ForceFixed::m7() {
    if (auto* controller = mActor->getCharacterController()) {
        if (!controller->mFlags.isOn(0x400))
            controller->mFlags.set(0x400);
        if (!controller->mFlags.isOn(0x800))
            controller->mFlags.set(0x800);
        if (!controller->mFlags.isOn(0x4))
            controller->sub_7100F62BC0(true);
    } else if (auto* body = mActor->getMainBody()) {
        if (!body->hasFlag(ksys::phys::RigidBody::Flag::Fixed))
            body->setFixed(ksys::phys::Fixed(true), ksys::phys::PreserveVelocities(false));
    }
}

void ForceFixed::m8() {
    if (auto* controller = mActor->getCharacterController()) {
        _28 = controller->mFlags.isOn(0x400);
        _29 = controller->mFlags.isOn(0x800);
        _2a = controller->mFlags.isOn(0x4);
        controller->mFlags.set(0x400 | 0x800);
        controller->sub_7100F62BC0(true);
    } else if (auto* body = mActor->getMainBody()) {
        _2b = body->hasFlag(ksys::phys::RigidBody::Flag::Fixed);
        body->setFixed(ksys::phys::Fixed(true), ksys::phys::PreserveVelocities(false));
    }
}

void ForceFixed::m9() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.change(0x400, _28);
        controller->mFlags.change(0x800, _29);
        controller->sub_7100F62BC0(_2a);
    } else if (auto* body = mActor->getMainBody()) {
        body->setFixed(ksys::phys::Fixed(_2b), ksys::phys::PreserveVelocities(true));
    }
}

void ForceFixed::loadParams() {}

}  // namespace uking::behavior
