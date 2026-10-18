#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include <math/seadBoundBox.h>
#include <algorithm>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
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

// NON_MATCHING: the first / second basis vectors end up in the reverse register order
// (s11,s10,s9 / s13,s12,s14 here vs s9,s10,s11 / s13,s14,s15 in the original); every other
// instruction matches.
void sub_7100EBFEA8(f32 scale, ::DamageReactionRequest* request, const sead::Vector3f& axis,
                    const sead::Vector3f& up, const sead::Vector3f& pos) {
    sead::Vector3f right = sead::Vector3f::ex;
    if (sead::Mathf::abs(axis.dot(up)) <= 0.999f)
        right = axis;

    sead::Vector3f front = up.cross(right);
    front.normalize();

    sead::Vector3f side = front.cross(up);
    side.normalize();

    request->mtx.m[0][0] = front.x;
    request->mtx.m[0][1] = up.x;
    request->mtx.m[0][2] = side.x;
    request->mtx.m[0][3] = pos.x;
    request->mtx.m[1][0] = front.y;
    request->mtx.m[1][1] = up.y;
    request->mtx.m[1][2] = side.y;
    request->mtx.m[1][3] = pos.y;
    request->mtx.m[2][0] = front.z;
    request->mtx.m[2][1] = up.z;
    request->mtx.m[2][2] = side.z;
    request->mtx.m[2][3] = pos.z;
    request->_3c = scale;
    request->_40 = scale;
    request->_44 = scale;
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

namespace ksys::act {

// NON_MATCHING: the request source getXLink helper inlines into the emitter.
void Reaction::Unk1::sub_7100EC539C(DamageReactionRequest* request,
                                  xlink2::HandleSLink* handle, const char* name) {
    xlink2::Locator locator;
    auto* xlink = request->mSource.getXLink();
    if (!xlink || !xlink->_50)
        return;
    auto* user = xlink->_50;
    if (!user->searchAsset(&locator, name))
        return;
    if (request->mSource.mActor || request->mSource.mLink) {
        if (auto* source = request->mSource.getXLink())
            sub_7100EC56D8(source, request);
    }
    user->emit(locator, handle);
    ksys::eft::sub_710105E060(handle, request->mtx);
}

// NON_MATCHING: the request source getXLink helper inlines into the tracking test.
void Reaction::Unk1::sub_7100EC447C(Actor* actor, DamageReactionRequest* request,
                                  xlink2::HandleSLink* handle, const char* name) {
    if (!actor)
        return;
    xlink2::Locator locator;
    auto* xlink = actor->getXLink();
    if (!xlink || !xlink->_50)
        return;
    auto* user = xlink->_50;
    if (!user->searchAsset(&locator, name))
        return;
    if (auto* source = actor->getXLink())
        sub_7100EC56D8(source, request);
    user->emit(locator, handle);
    ksys::eft::sub_710105E060(handle, request->mtx);
    if (!handle->isActive())
        return;
    bool track = request->_98 == 1;
    if (!track && u32(request->_90) < 29) {
        const u32 mask = 1u << request->_90;
        track = (mask & 0x180000c0) != 0;
        if (!track && (mask & 0xc02)) {
            if (auto* source = request->mSource.getXLink())
                track = source->_cc.isOnBit(6);
        }
    }
    if (track)
        snd::Unk_710104e5b4::instance()->sub_710104FA78(*handle);
}

// NON_MATCHING: clamp, material and sound-handle branches use different temporary storage.
bool Reaction::Unk1::sub_7100EC5C40(f32 speed, f32 value, Actor* actor,
                                   const sead::Vector3f& position, s32 size, u32 flags,
                                   const phys::MaterialMask* mask) {
    if (!actor || actor->get4f8() > 0.0f)
        return false;
    if (actor->getActorFlags2().isOn(Actor::ActorFlag2::_1) ||
        actor->getActorFlags2().isOn(Actor::ActorFlag2::_20))
        return false;
    const bool player = isPlayerProfile(actor);
    if (player) {
        if (auto* link = ActorSystem::instance()->getPlayerLink()) {
            if (link->m186())
                value = sead::Mathf::min(value, 0.15f);
        }
        if (mask && int(mask->getMaterial()) == 35) {
            if (_118 > 0)
                return false;
            _118 = 2;
        }
    }
    s32 material;
    s32 submaterial;
    if (mask) {
        material = int(mask->getMaterial());
        submaterial = phys::MaterialMask::getSubMaterialIdx(
            mask->getMaterial(), mask->getSubMaterialName());
    } else {
        material = actor->get6fc();
        submaterial = actor->get700();
    }
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50) {
            user->setPropertyValue(0, material);
            user->setPropertyValue(1, xlink::Manager::instance()->getSubMaterialIndex(material, submaterial));
            user->setPropertyValue(10, speed / 30.0f);
            user->setPropertyValue(4, speed);
            user->setPropertyValue(5, value);
            xlink2::HandleSLink handle;
            if (!(flags & 1))
                handle = user->searchAndEmit("ReactionWaterSink");
            if ((flags & 1) || !handle.isActive())
                handle = user->searchAndEmit("ReactionWaterHit");
            if (handle.isActive()) {
                handle.setPosition(position);
                eft::sub_710105E114(&handle, actor);
                return true;
            }
        }
    }
    auto* xlink = _8->getXLink();
    if (!xlink || !xlink->_50)
        return false;
    auto* user = xlink->_50;
    if (!player && mSLinkLimiter && !mSLinkLimiter->sub_7100EC9D84(3, position, false))
        return false;
    const f32 magnitude = speed > 0.0f ? speed : -speed;
    if (magnitude < 0.1f)
        return false;
    user->setPropertyValue(9, speed / 30.0f);
    user->setPropertyValue(4, speed);
    user->setPropertyValue(6, size);
    user->setPropertyValue(5, value);
    user->setPropertyValue(0, material);
    user->setPropertyValue(1, xlink::Manager::instance()->getSubMaterialIndex(material, submaterial));
    auto handle = user->searchAndEmit("ReactionWaterHit");
    if (!handle.isActive())
        return false;
    handle.setPosition(position);
    eft::sub_710105E114(&handle, actor);
    if (!player && mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(3, position, handle);
    return true;
}

void Reaction::Unk1::sub_7100EC5B64(const sead::Vector3f& position) {
    if (!_10)
        return;
    const f32 elapsed = eft::sub_710105E0AC(mGrassCutHandle);
    if (!(elapsed >= 0.0f && elapsed <= 0.3f)) {
        mGrassCutHandle = eft::searchAndEmitSLink(_10, "GrassCut", false);
        mGrassCutHandle.setPosition(position);
    }
}

bool Reaction::Unk1::sub_7100EC5C30(f32 speed, f32 value, Actor* actor,
                                   const sead::Vector3f& position) {
    return sub_7100EC5C40(speed, value, actor, position, 2, 1, nullptr);
}

// NON_MATCHING: submaterial extraction and the singleton load are scheduled differently.
void Reaction::sub_7100EC29D0(Actor* actor) {
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    sead::Vector3f start = actor->getMtx().getTranslation();
    start.y += 2.0f;
    sead::Vector3f end = start;
    end.y -= 10.0f;
    query.setStart(start);
    query.setEnd(end);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.enableLayer(phys::ContactLayer::EntityGroundRough);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return;
    sead::Vector3f position;
    query.getHitPosition(&position);
    const auto& mask = query.getMaterialMask();
    const s32 material = int(mask.getMaterial());
    const s32 submaterial = xlink::Manager::instance()->getSubMaterialIndex(material, mask.getSubMaterialIdx());
    if (auto* user = actor->getXLink()->_48) {
        user->setPropertyValue(0, material);
        user->setPropertyValue(1, submaterial);
    }
    if (auto* user = actor->getXLink()->_50) {
        user->setPropertyValue(0, material);
        user->setPropertyValue(1, submaterial);
    }
}

// NON_MATCHING: shared reference-vector loads and matrix store scheduling differ.
void sub_7100EBFB5C(f32 scale, DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position) {
    sead::Vector3f axis = sead::Vector3f::ex;
    if (sead::Mathf::abs(sead::Vector3f::ez.dot(up)) <= 0.999f)
        axis = sead::Vector3f::ez;
    sead::Vector3f front = up.cross(axis);
    front.normalize();
    sead::Vector3f side = front.cross(up);
    side.normalize();
    request->mtx.setBase(0, front);
    request->mtx.setBase(1, up);
    request->mtx.setBase(2, side);
    request->mtx.setTranslation(position);
    request->_3c = scale;
    request->_40 = scale;
    request->_44 = scale;
}

// NON_MATCHING: shared reference-vector loads and matrix store scheduling differ.
void sub_7100EBFD08(f32 scale, DamageReactionRequest* request, const sead::Vector3f& up,
                    const sead::Vector3f& position) {
    sead::Vector3f axis = sead::Vector3f::ex;
    if (sead::Mathf::abs(sead::Vector3f::ey.dot(up)) <= 0.999f)
        axis = sead::Vector3f::ey;
    sead::Vector3f front = axis.cross(up);
    front.normalize();
    sead::Vector3f side = up.cross(front);
    side.normalize();
    request->mtx.setBase(0, front);
    request->mtx.setBase(1, side);
    request->mtx.setBase(2, up);
    request->mtx.setTranslation(position);
    request->_3c = scale;
    request->_40 = scale;
    request->_44 = scale;
}

}  // namespace ksys::act

namespace ksys::act {
// NON_MATCHING: velocity length and translation-copy scheduling differ.
void Reaction::Unk1::sub_7100EC6070(f32 value, DamageReactionRequest* request, bool flag) {
    if (!_8 || !request->_b8)
        return;
    auto* xlink = _8->getXLink();
    if (!xlink || !xlink->_50)
        return;
    auto* user = xlink->_50;
    user->setPropertyValue(3, request->_b8->getVelocity().length());
    user->setPropertyValue(18, value);
    user->setPropertyValue(19, s32(flag));
    const auto position = request->mtx.getTranslation();
    if (mSLinkLimiter && !mSLinkLimiter->sub_7100EC9D84(10, position, false))
        return;
    auto handle = eft::searchAndEmitSLink(_8, "GrassTrack", false);
    if (!handle.isActive())
        return;
    handle.setPosition(position);
    eft::sub_710105E114(&handle, request->_b8);
    if (mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(10, position, handle);
}

}  // namespace ksys::act

namespace ksys::act {
// NON_MATCHING: bounding-box temporaries and delay-emission matrix stores differ.
void Unk_7101286868::sub_7101286BF8(xlink2::HandleELink* handle,
                                   DamageReactionRequest* request) {
    auto* actor = request->_b8;
    if (actor && actor->getXLink()) {
        if (auto* user = actor->getXLink()->_48)
            user->setPropertyValue(4, request->_54);
        *handle = eft::searchAndEmitELink(actor, "BitaLocked_Start");
    }
    if (!handle->isActive()) {
        auto* source = _38;
        if (auto* user = source->getXLink()->_48)
            user->setPropertyValue(4, request->_54);
        *handle = eft::searchAndEmitELink(source, "BitaLocked_Start");
    }
    if (actor) {
        const auto position = request->mtx.getTranslation();
        f32 scale = 1.0f;
        if (auto* model = actor->getModel()) {
            if (auto* unit = model->getUnits()[0]->mModelUnit) {
                sead::BoundBox3f bounds;
                unit->calcBoundAABB(&bounds, false);
                const auto size = bounds.getMax() - bounds.getMin();
                scale = sead::Mathf::max(size.x, size.y);
                scale = sead::Mathf::max(scale, size.z);
            }
        }
        sead::Matrix34f matrix;
        matrix.makeS(scale, scale, scale);
        matrix.setTranslation(position);
        handle->setMatrix(matrix);
    }
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: rideable enum switches and vector temporaries use different layouts.
void Reaction::Unk1::sub_7100EC56D8(xlink::XLink* xlink, DamageReactionRequest* request) {
    static_assert(offsetof(xlink::Manager, mPropertyDefinitionSets) == 0x150);
    auto* user = xlink->_50;
    if (!user)
        return;
    switch (request->_90) {
    case 0xc:
    case 0xd:
        if (request->_b8) {
            if (auto* rideable = request->_b8->m132()) {
                s32 type = 1;
                switch (rideable->_18._a) {
                case 0: type = 0; break;
                case 1: type = 1; break;
                case 2: type = 2; break;
                case 3: type = 3; break;
                }
                user->setPropertyValue(17, type);
                const u8 gear = rideable->_18._b ? rideable->_18._b : rideable->_18._9;
                s32 value = 1;
                switch (gear) {
                case 0: value = 0; break;
                case 1: value = 1; break;
                case 2: value = 2; break;
                case 3: value = 3; break;
                case 4: value = 4; break;
                }
                user->setPropertyValue(16, value);
            }
        }
        break;
    case 0xf: {
        user->setPropertyValue(10, request->_58);
        auto direction = request->_b8->getVelocity();
        const auto forward = request->_b8->getMtx().getBase(2);
        direction.normalize();
        user->setPropertyValue(15, forward.dot(direction));
        break;
    }
    case 0x11:
        if (request->_b8) {
            if (auto* rideable = request->_b8->m132()) {
                const u8 gear = rideable->_18._b ? rideable->_18._b : rideable->_18._9;
                s32 value = 1;
                switch (gear) {
                case 2: value = 2; break;
                case 3: value = 3; break;
                case 4: value = 4; break;
                }
                user->setPropertyValue(16, value);
                s32 type = 1;
                switch (rideable->_18._a) {
                case 0: type = 0; break;
                case 2: type = 2; break;
                case 3: type = 3; break;
                }
                user->setPropertyValue(17, type);
            }
        }
        break;
    case 0x18:
        return;
    }
    auto* manager = xlink::Manager::instance();
    if (xlink->mPropertyDefinitions == manager->mPropertyDefinitionSets[16])
        user->setPropertyValue(25, request->_94);
    else if (xlink->mPropertyDefinitions == manager->mPropertyDefinitionSets[26])
        user->setPropertyValue(8, request->_94);
    const sead::Vector3f velocity(request->_48, request->_4c, request->_50);
    user->setPropertyValue(3, velocity.length());
    user->setPropertyValue(4, request->_54);
    user->setPropertyValue(6, request->_c0);
    if (auto* actor = request->_b8) {
        const f32 depth = actor->get68f() ? actor->get6f0() - actor->getMtx().getTranslation().y : 0.0f;
        user->setPropertyValue(5, depth);
    }
    const s32 material = int(request->_78.getMaterial());
    user->setPropertyValue(0, material);
    user->setPropertyValue(1, manager->getSubMaterialIndex(material, request->_78.getSubMaterialIdx()));
    f32 wet;
    if (material == 8)
        wet = 1.0f;
    else if (request->_b8 && (request->_b8->_6a0->_10._8 & 8))
        wet = 0.0f;
    else
        wet = world::Manager::instance()->getWeatherMgrUnchecked()->_2d0;
    user->setPropertyValue(7, std::max(request->_9c, wet));
}

}  // namespace ksys::act
