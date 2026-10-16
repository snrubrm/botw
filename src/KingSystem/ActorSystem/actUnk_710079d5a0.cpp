// Unk_7102459df8::Unk_710079d5a0 (TU from 0x79f600, separate from Unk_7102459df8: not inlined into it).
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::act {

Unk_7102459df8::Unk_710079d5a0::Unk1::Unk1() = default;

void Unk_7102459df8::Unk_710079d5a0::sub_710079F600() {
    for (int i = 0; i < mNum; ++i) {
        mEntries[i].resetFlags();
        mEntries[i]._50.reset();
    }
    mNum = 0;
    _582 = 0;
}

// NON_MATCHING: the original re-reads the buffer entry for each iterator and keeps the begin iterator in
// another stack slot; regalloc.
void Unk_7102459df8::Unk_710079d5a0::sub_710079F66C(sead::Buffer<phys::ContactPointInfo*>* buffer,
                                                    Actor* actor) {
    for (int i = 0; i < mNum; ++i) {
        mEntries[i].resetFlags();
        mEntries[i]._50.reset();
    }
    mNum = 0;

    for (auto* info : *buffer) {
        if (info->getNumContactPoints() == 0 || info->begin().isEnd())
            continue;
        auto it = info->begin();
        const auto end = info->end();
        for (; it != end; ++it) {
            auto* body = it.getPoint()->body_b;
            auto* tag = sead::DynamicCast<PhysicsUserTag>(body->getUserTag());
            if (!tag)
                continue;
            auto* own_tag = sead::DynamicCast<PhysicsUserTag>(it.getPoint()->body_a->getUserTag());
            if (!own_tag)
                continue;
            auto* own_actor = own_tag->getActor(nullptr, actor);
            if (!own_actor)
                continue;
            ActorLinkConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasProc(own_actor))
                continue;
            if (mNum > 7)
                return;
            auto& entry = mEntries[mNum];
            const sead::Vector3f position =
                it.getPointPosition(phys::ContactPointInfo::Iterator::Point::BodyA);
            body->getRigidBodyAccessor()->getTransform(&entry._60);
            const sead::Vector3f normal = -it.getPoint()->separating_normal;
            entry.beamLevelStuff(position, normal, it.getPoint()->material_mask_b,
                                 it.getPoint()->material_mask_a, nullptr, nullptr);
            body->getRigidBodyAccessor()->getLinearVelocity(&entry._90);
            entry._a8 = body->getMass();
            accessor.linkAcquireImmediately(&entry._50);
            entry.sub_710079FC50(body);
            ++mNum;
        }
    }
}

// NON_MATCHING: the original takes the first list node before locking the collision info; regalloc.
void Unk_7102459df8::Unk_710079d5a0::sub_710079F9C0(sead::Buffer<phys::CollisionInfo*>* buffer,
                                                    Actor* actor) {
    for (auto* info : *buffer) {
        if (info->getCollidingBodies().size() == 0)
            continue;
        info->lock();
        for (auto& bodies : info->getCollidingBodies()) {
            auto* tag_b = sead::DynamicCast<PhysicsUserTag>(bodies.bodies[1]->getUserTag());
            if (!tag_b)
                continue;
            auto* tag_a = sead::DynamicCast<PhysicsUserTag>(bodies.bodies[0]->getUserTag());
            if (!tag_a)
                continue;
            auto* other = tag_a->getActor(nullptr, actor);
            if (!other)
                continue;
            ActorLinkConstDataAccess accessor;
            tag_b->acquireActor(&accessor);
            if (!accessor.hasProc(other)) {
                _582 = true;
                if (_588)
                    _588(other, &accessor, bodies.bodies[0], bodies.bodies[1]);
            }
        }
        info->unlock();
    }
}

// NON_MATCHING: the original keeps `pos` on the stack (in the slot of `velocity`); ours keeps it in registers.
void Unk_7102459df8::Unk_710079d5a0::Unk1::sub_710079FC50(phys::RigidBody* body) {
    sead::Vector3f angular_velocity;
    body->getAngularVelocity(&angular_velocity);
    const f32 angular_speed = angular_velocity.length();
    if (angular_speed > 0.0f)
        angular_velocity *= 0.7853982f / angular_speed;  // pi / 4

    sead::Vector3f velocity;
    body->getRigidBodyAccessor()->getLinearVelocity(&velocity);
    velocity.normalize();

    sead::Vector3f offset = velocity;
    sead::Vector3f pos = _0;
    util::sub_71011EFB40(&offset, angular_velocity);
    pos += offset;
    util::sub_71011EFB40(&offset, angular_velocity);
    pos += offset;
    pos -= _0;
    pos.normalize();

    // Both results are unused.
    sead::Vector3f unused_body_velocity;
    body->getAngularVelocity(&unused_body_velocity);
    sead::Vector3f unused_accessor_velocity;
    body->getRigidBodyAccessor()->getAngularVelocity(&unused_accessor_velocity);

    _9c = pos;
}

}  // namespace ksys::act
