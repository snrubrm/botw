#include "Game/Actor/actMotorcycleUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

// NON_MATCHING: register allocation of the last product only
f32 innerProductTimesA3(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b) {
    const f32 dot = a.dot(b);
    out->x = b.x * dot;
    out->y = b.y * dot;
    out->z = dot * b.z;
    return dot;
}

// NON_MATCHING: load / multiply scheduling only
f32 perpendicularPart(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b) {
    const f32 dot = a.dot(b);
    out->x = a.x - b.x * dot;
    out->y = a.y - b.y * dot;
    out->z = a.z - b.z * dot;
    return dot;
}

// NON_MATCHING: register allocation / load scheduling only
f32 splitParallelPerpendicular(sead::Vector3f* parallel, sead::Vector3f* perpendicular,
                                const sead::Vector3f& a, const sead::Vector3f& b) {
    *perpendicular = a;
    const f32 dot = a.dot(b);
    parallel->x = b.x * dot;
    parallel->y = b.y * dot;
    parallel->z = dot * b.z;
    perpendicular->x -= parallel->x;
    perpendicular->y -= parallel->y;
    perpendicular->z -= parallel->z;
    return dot;
}

// NON_MATCHING: the original adds `x + velocity.x` (argument first), every source form gives `velocity.x + x`
void addLinearVelocity(ksys::phys::RigidBody* body, f32 x, f32 y, f32 z) {
    body->setLinearVelocity(sead::Vector3f(x, y, z) + body->getLinearVelocity());
}

// NON_MATCHING: as addLinearVelocity
void addAngularVelocity(ksys::phys::RigidBody* body, f32 x, f32 y, f32 z) {
    body->setAngularVelocity(sead::Vector3f(x, y, z) + body->getAngularVelocity());
}

bool isTurnOffTouchMotorcycle(ksys::phys::RigidBody* body) {
    if (auto* user_tag = body->getUserTag()) {
        if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(user_tag)) {
            ksys::act::ActorConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasTag(ksys::act::tags::IsTurnOffTouchMotorcycle))
                return true;
        }
    }
    return false;
}

}  // namespace uking::act
