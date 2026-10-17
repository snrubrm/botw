#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <thread/seadThread.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

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

// NON_MATCHING: the zero body-index argument is prepared in a 32-bit register.
void PhysicsConstraints::calc() {
    if (_11)
        return;
    s32 ready = 0;
    for (auto* constraint : mConstraints) {
        if (!constraint)
            return;
        if (constraint->_50 & 1) {
            ++ready;
            continue;
        }
        auto* body_a = constraint->x_0(0);
        auto* body_b = constraint->x_0(1);
        if (!body_a || (!body_a->isAddedToWorld() && !body_a->isAddingBodyToWorld()))
            continue;
        if (body_b && !body_b->isAddedToWorld() && !body_b->isAddingBodyToWorld())
            continue;
        constraint->sub_7100F69FF0();
        ++ready;
    }
    _11 = ready == mConstraints.size();
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

void PhysicsConstraints::sub_7100D403A8() {
    for (auto* constraint : mConstraints) {
        if (constraint)
            constraint->sub_7100F6A21C();
    }
}

void PhysicsConstraints::sub_7100D40194(phys::RigidBody* body) {
    if (!tera::checkTeraSystemStatus()) {
        if (!sead::ThreadMgr::instance()->getCurrentThread()->isDefaultPriority())
            return;
        if (BaseProcMgr::instance()->isPushingJobs())
            return;
    }
    for (auto* constraint : mConstraints) {
        if (constraint && constraint->x_0(1) == body)
            constraint->sub_7100F6A92C(nullptr);
    }
}

}  // namespace ksys::act
