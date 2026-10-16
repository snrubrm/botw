#include "Game/Actor/Behavior/behaviorOctarockConstraint.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

OctarockConstraint::OctarockConstraint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockConstraint::~OctarockConstraint() = default;

bool OctarockConstraint::init_(sead::Heap* heap) {
    return true;
}

void OctarockConstraint::calc() {}

void OctarockConstraint::loadParams() {

}

void OctarockConstraint::enter() {
    if (auto* cc = mActor->getCharacterController())
        cc->mFlags.set(0xc00);
}

void OctarockConstraint::leave() {
    if (auto* cc = mActor->getCharacterController())
        cc->mFlags.reset(0xc00);
}

}  // namespace uking::behavior
