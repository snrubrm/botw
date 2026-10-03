#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace ksys::act {

PhysicsConstraints::PhysicsConstraints() = default;

PhysicsConstraints::~PhysicsConstraints() {
    finalize();
}

void PhysicsConstraints::finalize() {
    for (auto*& cs : mConstraints) {
        if (cs) {
            phys::Constraint::destroy(cs);
            cs = nullptr;
        }
    }
    mConstraints.freeBuffer();
    _10 = false;
    _11 = false;
}

bool PhysicsConstraints::sub_7100D40338() {
    bool result = false;
    for (auto* cs : mConstraints) {
        if (cs && ((cs->_50 & 1) || cs->sub_7100F6ACE8())) {
            cs->sub_7100F6A074();
            result = true;
        }
    }
    return result;
}

}  // namespace ksys::act
