#include "Game/AI/Behavior/behaviorOctarockConstraint.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

OctarockConstraint::OctarockConstraint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockConstraint::~OctarockConstraint() = default;

bool OctarockConstraint::m6(sead::Heap* heap) {
    return true;
}

void OctarockConstraint::m7() {}

void OctarockConstraint::loadParams() {

}

void OctarockConstraint::m8() {
    if (auto* cc = mActor->getCharacterController())
        cc->mFlags.set(0xc00);
}

void OctarockConstraint::m9() {
    if (auto* cc = mActor->getCharacterController())
        cc->mFlags.reset(0xc00);
}

}  // namespace uking::behavior
