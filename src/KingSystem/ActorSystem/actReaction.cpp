#include "KingSystem/ActorSystem/actReaction.h"
#include <math/seadBoundBox.h>
#include <algorithm>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::act {
Reaction* Reaction::sInstance;

xlink::XLink* Unk_7100ebf9e4::getXLink() const {
    if (mActor)
        return mActor->getXLink();
    if (!mLink)
        return nullptr;
    ActorLinkConstDataAccess accessor;
    acquireActor(mLink, &accessor);
    return accessor.sub_7100D0F214();
}

s32 Unk_7100ebf9e4::getChemicalState() const {
    if (mLink) {
        ActorLinkConstDataAccess accessor;
        acquireActor(mLink, &accessor);
        return accessor.sub_7100D131D0(-1);
    }
    if (mActor) {
        if (auto* chemical = mActor->getChemicalStuff())
            return chemical->_c0;
    }
    return 0;
}

const sead::SafeString& Unk_7100ebf9e4::getName() const {
    if (mLink) {
        ActorLinkConstDataAccess accessor;
        acquireActor(mLink, &accessor);
        if (accessor.hasProc())
            return accessor.getName();
    } else if (mActor) {
        return mActor->getName();
    }
    return sead::SafeString::cEmptyString;
}

void Reaction::Unk1::sub_7100EC66FC(Actor* actor) {
    _110 = 2;
}

f32 Reaction::Unk1::sub_7100EC877C() const {
    return 0.7f;
}

s32 Reaction::Unk1::sub_7100EC87A4() const {
    return 7;
}

s8 Reaction::Unk1::sub_7100EC89BC() const {
    return 5;
}

// NON_MATCHING: min / max operand order, the 2 / 3 choice becomes a csel, and the size is returned as a
// 64-bit register move.
u32 Reaction::sub_7100EC2278(Actor* actor, bool* is_long) {
    if (auto* body = actor->getMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        const f32 x = aabb.getSizeX();
        const f32 y = aabb.getSizeY();
        const f32 z = aabb.getSizeZ();
        const f32 min_xy = std::min(x, y);
        const f32 max_xy = std::max(x, y);
        const f32 min = std::min(min_xy, z);
        const f32 max = std::max(max_xy, z);

        s32 size;
        if (max < 0.4f)
            size = 0;
        else if (max < 0.75f)
            size = 1;
        else if (min > 3.0f)
            size = 4;
        else if (min > 1.5f)
            size = 3;
        else
            size = 2;

        if (is_long) {
            const bool is_large = max > 4.5f;
            const bool is_thin = min / max < 0.35f;
            const bool is_flat = (x + y + z - min - max) / max < 0.35f;
            *is_long = is_large && is_thin && is_flat;
        }
        return size;
    }

    s32 size = 2;
    if (auto* body = actor->getPhysicsMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        size = aabb.getMax().y - aabb.getMin().y < 2.2f ? 2 : 3;
    }
    if (is_long)
        *is_long = false;
    return size;
}

bool Reaction::sub_7100EC2980(Actor* actor) {
    if (_b0 && _a8)
        return _a8->sub_7100EC6DD0(actor);
    return false;
}

void Reaction::sub_7100EC299C(f32 value, DamageReactionRequest* request, bool flag) {
    if (_b0 && _a8)
        _a8->sub_7100EC6070(value, request, flag);
}

void Reaction::sub_7100EC29B8(DamageReactionRequest* request) {
    if (_b0 && _a8)
        _a8->sub_7100EC61F8(request);
}

// NON_MATCHING: the actor size stays 64-bit and is zero-extended (target `mov x8,x0` / `and x23,
// x8,#0xffffffff`); ours truncates to 32 bits when the u32 return is stored.
void Reaction::sub_7100EC241C(Actor* actor, phys::UserTag::Unk5* info) {
    if (!_b0)
        return;

    actor->set6e4(15.0f);

    auto* body = info->_20;
    if (body->getContactLayer() == phys::ContactLayer::EntityRagdoll)
        return;

    phys::MaterialMask mask;
    switch (info->_d) {
    case 2:
        mask = phys::MaterialMask(u32(0xb));
        break;
    case 1:
        mask = phys::MaterialMask(u32(0xc));
        break;
    default:
        mask = phys::MaterialMask(u32(8));
        break;
    }

    sead::Vector3f velocity = actor->getVelocity();
    velocity.x *= info->_28.x;
    velocity.y *= info->_28.y;
    velocity.z *= info->_28.z;
    const f32 speed = velocity.length();

    const u64 size = Reaction::instance()->sub_7100EC2278(actor, nullptr);
    if (_a8 && _a0) {
        const u32 material = mask.getRawData() & 0x3f;
        _a8->sub_7100EC8F78(speed, actor, &info->_10, size, material, 0);
        _a0->sub_7101286868(speed, actor, &info->_10, &info->_28, size, material, 0);
    }
}

// NON_MATCHING: register naming (s13 / s14) and the stack slots of the two ray directions differ.
void Reaction::sub_7100EC2598(Actor* actor) {
    if (!_b0)
        return;

    actor->set6e4(15.0f);

    auto* body = actor->getPhysicsMainBody();
    if (!body)
        return;
    if (body->hasFlag(phys::RigidBody::Flag::_1000000))
        return;
    if (body->hasFlag(phys::RigidBody::Flag::FixedWithImpulsePreserved))
        return;
    if (actor->get4f8() > 0.0f)
        return;

    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const sead::Vector3f velocity = actor->getVelocity();
    sead::Vector3f dir = velocity;
    dir.normalize();

    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.setStart(sead::Vector3f{pos.x + dir.x * 5.0f, pos.y + dir.y * 5.0f,
                                  pos.z + dir.z * 5.0f});
    query.setEnd(sead::Vector3f{pos.x - dir.x * 10.0f, pos.y - dir.y * 10.0f,
                                pos.z - dir.z * 10.0f});

    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return;

    sead::Vector3f hit_pos;
    query.getHitPosition(&hit_pos);
    sead::Vector3f hit_normal;
    query.getHitNormal(&hit_normal);

    sead::Vector3f scaled{velocity.x * hit_normal.x, velocity.y * hit_normal.y,
                          velocity.z * hit_normal.z};
    const f32 speed = scaled.length();

    const u64 size = Reaction::instance()->sub_7100EC2278(actor, nullptr);
    if (_a8 && _a0) {
        const u32 material = actor->get6fc();
        _a8->sub_7100EC8F78(speed * 10.0f, actor, &hit_pos, size, material, 1);
        _a0->sub_7101286868(speed, actor, &hit_pos, &hit_normal, size, material, 1);
    }
}

// NON_MATCHING: the query object and the two temporary vectors land in different stack slots (frame 0x150
// vs the target's 0x160) and the start / end stores are not paired.
void Reaction::sub_7100EC27FC(Actor* actor) {
    if (!_b0)
        return;

    actor->set6e4(15.0f);

    auto* body = actor->getPhysicsMainBody();
    if (!body)
        return;
    if (body->hasFlag(phys::RigidBody::Flag::_1000000))
        return;
    if (body->hasFlag(phys::RigidBody::Flag::FixedWithImpulsePreserved))
        return;
    if (actor->get4f8() > 0.0f)
        return;

    const sead::Vector3f pos = actor->getMtx().getTranslation();

    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.setStart(sead::Vector3f{pos.x, pos.y + 5.0f, pos.z});
    query.setEnd(sead::Vector3f{pos.x, pos.y - 10.0f, pos.z});

    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return;

    sead::Vector3f hit_pos;
    query.getHitPosition(&hit_pos);
    sead::Vector3f hit_normal;
    query.getHitNormal(&hit_normal);

    const u64 size = Reaction::instance()->sub_7100EC2278(actor, nullptr);
    if (_a8 && _a0) {
        const u32 material = actor->get6fc();
        _a8->sub_7100EC8F78(10.0f, actor, &hit_pos, size, material, 2);
        _a0->sub_7101286868(1.0f, actor, &hit_pos, &hit_normal, size, material, 2);
    }
}

}  // namespace ksys::act
