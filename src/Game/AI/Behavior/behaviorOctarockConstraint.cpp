#include "Game/AI/Behavior/behaviorOctarockConstraint.h"

namespace uking::behavior {

OctarockConstraint::OctarockConstraint(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockConstraint::~OctarockConstraint() = default;

bool OctarockConstraint::m6(sead::Heap* heap) {
    return true;
}

void OctarockConstraint::m7() {}

void OctarockConstraint::loadParams() {

}

}  // namespace uking::behavior
