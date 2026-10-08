#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

PhysicsUserTag::PhysicsUserTag(Actor* actor) : mActor(actor) {}

PhysicsUserTag::~PhysicsUserTag() = default;

Actor* PhysicsUserTag::getActor(ActorLinkConstDataAccess* accessor, Actor* other_actor) const {
    if (mActor != nullptr) {
        if (mActor != other_actor && !BaseProcMgr::instance()->isAccessingProcSafe(mActor, nullptr))
            return mActor;
        if (!acquireProc(accessor, mActor, "act::PhysicsUserTag"))
            return nullptr;
    }
    return mActor;
}

bool PhysicsUserTag::acquireActor(ActorLinkConstDataAccess* accessor) const {
    return accessor->acquire(mActor);
}

void PhysicsUserTag::onMaxPositionExceeded(phys::RigidBody* body) {
    mActor->m92(body);
}

void PhysicsUserTag::onImpulse(phys::RigidBody* body_a, phys::RigidBody* body_b, float impulse_a) {
    // The tag hash is not identified.
    constexpr u32 tag = 0x2c608f30;

    auto* actor = mActor;
    const bool fixed = body_a->hasFlag(phys::RigidBody::Flag::Fixed);
    if (!fixed || !hasTag(actor, tag)) {
        if (fixed) {
            sead::Vector3f com_a;
            body_a->getCenterOfMassInWorld(&com_a);
            sead::Vector3f com_b;
            body_b->getCenterOfMassInWorld(&com_b);

            sead::Vector3f dir = com_a - com_b;
            dir.normalize();
            actor->m36(sead::Vector3f(dir.x * impulse_a, dir.y * impulse_a, dir.z * impulse_a),
                       body_b->getPosition(), false, true, false);
        }
        actor->m35(impulse_a, body_a, body_b);
    }

    // inline-only in the original: the body of LodState::sub_710125122C
    if (auto* lod = actor->getLodState()) {
        lod->mFlags8.reset(0x40);
        lod->_60 = 0;
    }
}

const sead::SafeString& PhysicsUserTag::getName() const {
    return mActor->getName();
}

void PhysicsUserTag::m7(phys::RigidBody* rigid_body, int a) {
    mActor->nullsub_4649();
}

const sead::SafeString& PhysicsUserTag::getName(phys::RigidBody* rigid_body) const {
    return getName();
}

}  // namespace ksys::act
