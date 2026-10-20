#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
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
#include "Game/gameGraphics.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/physMaterialMask.h"

// Original enum ownership and source namespace are unknown; declaration only.
// Existing FootstepReactionChanger callers use the same ABI.
const char* sub_7100E367C0(s32 index);

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
void Reaction::sub_7100EC1C24(Actor* actor, const phys::MaterialMask& mask) const {
    if (!actor)
        return;
    const int material = mask.getMaterial();
    const int sub_material_idx = mask.getSubMaterialIdx();
    const int sub_material =
        xlink::Manager::instance()->getSubMaterialIndex(material, sub_material_idx);
    f32 wetness;
    if (material == 8 && sead::SafeString(mask.getSubMaterialName()) == "Water_StoneBottom")
        wetness = 1.0f;
    else if (actor->_6a0->_10._8 & 8)
        wetness = 0.0f;
    else
        wetness = world::Manager::instance()->getWeatherMgrUnchecked()->_2d0;
    auto* xlink = actor->getXLink();
    if (!xlink)
        return;
    if (auto* user = xlink->_48) {
        user->setPropertyValue(0, material);
        user->setPropertyValue(1, sub_material);
        user->setPropertyValue(7, wetness);
    }
    if (auto* user = xlink->_50) {
        user->setPropertyValue(0, material);
        user->setPropertyValue(1, sub_material);
        user->setPropertyValue(7, wetness);
    }
}

f32 Reaction::sub_7100EC1D98(const sead::Vector3f& pos) const {
    f32 height = -9999.0f;
    if (::Graphics::instance()->getMapStateMaybe() > 1)
        return height;
    auto* terrain = tera::Terrain::instance();
    if (!terrain || !terrain->isGrassEnabled())
        return height;
    auto* placement = map::PlacementMgr::instance();
    if (!placement || !placement->mTeraSystem)
        return height;
    sead::Vector2f xz{pos.x, pos.z};
    tera::sub_71011094A0(&height, &xz, placement->mTeraSystem, -1, 0);
    return height;
}

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
        snd::ExpressionSoundCtrl::instance()->sub_710104FA78(*handle);
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

namespace ksys::act {

// NON_MATCHING: sound-handle active checks use a different branch layout.
bool Reaction::Unk1::sub_7100EC64FC(f32 speed, xlink::XLink* xlink,
                                  const sead::Vector3f& position) {
    if (mSLinkLimiter && !mSLinkLimiter->sub_7100EC9D84(10, position, false))
        return true;
    xlink2::HandleSLink handle;
    if (xlink) {
        if (auto* user = xlink->_50) {
            user->setPropertyValue(3, speed);
            handle = user->searchAndEmit("BushTrack");
            if (handle.isActive()) {
                handle.setPosition(position);
                eft::sub_710105E214(&handle, false);
            }
        }
    }
    if (!handle.isActive()) {
        if (auto* user = _8->getXLink()->_50) {
            user->setPropertyValue(3, speed);
            handle = user->searchAndEmit("BushTrack");
            if (handle.isActive()) {
                handle.setPosition(position);
                eft::sub_710105E214(&handle, false);
            }
        }
    }
    if (handle.isActive() && mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(10, position, handle);
    return handle.isActive();
}

// NON_MATCHING: vector temporaries and return branches differ.
bool Reaction::Unk1::sub_7100EC6408(map::Unk_71012497f8Entry* entry) {
    if (mHasBushTrack)
        return false;
    if (InfoData::instance()->hasTag(entry->mName.cstr(), 0xe91ea5f6) &&
        (entry->mPosition - mBushTrackPosition).length() < 1.0f && entry->_80) {
        if (sub_7100EC64FC(mBushTrackSpeed, entry->mXLink, mBushTrackPosition)) {
            mHasBushTrack = true;
            return false;
        }
    }
    return true;
}

// NON_MATCHING: delegate storage and traversal use different temporaries.
void Reaction::Unk1::sub_7100EC61F8(DamageReactionRequest* request) {
    const auto position = request->mtx.getTranslation();
    mBushTrackPosition = position;
    mBushTrackSpeed = request->_b8->getVelocity().length();
    mHasBushTrack = false;
    if (auto* manager = map::PlacementMgr::instance()) {
        sead::Delegate1R<Unk1, map::Unk_71012497f8Entry*, bool> callback(
            this, &Unk1::sub_7100EC6408);
        manager->sub_71011EB40C(&position, 0.5f, &callback);
        if (mHasBushTrack)
            return;
    }
    if (_110 > 0) {
        if (sub_7100EC64FC(mBushTrackSpeed, nullptr, mBushTrackPosition)) {
            mHasBushTrack = true;
            return;
        }
        if (mHasBushTrack)
            return;
    }
    if (auto* manager = map::PlacementMgr::instance()) {
        const auto& objects = manager->mTraverseResults[1 - manager->mTraverseResultIdx]._70;
        for (s32 i = 0; i < objects.size(); ++i) {
            auto* object = objects[i];
            if ((object->getTranslate() - mBushTrackPosition).length() <= 0.8f) {
                ActorLinkConstDataAccess accessor;
                object->getActorWithAccessor(accessor);
                auto* xlink = accessor.sub_7100D0F214();
                if (xlink && sub_7100EC64FC(mBushTrackSpeed, xlink, mBushTrackPosition)) {
                    mHasBushTrack = true;
                    return;
                }
            }
        }
    }
}

// NON_MATCHING: model position and tracking conditions use different branches.
void Reaction::Unk1::sub_7100EC545C(xlink2::HandleSLink* handle,
                                  DamageReactionRequest* request) {
    xlink2::Locator locator;
    auto* xlink = _10->getXLink();
    if (!xlink || !xlink->_50)
        return;
    auto* user = xlink->_50;
    if (!user->searchAsset(&locator, sub_7100E367C0(request->_90)))
        return;
    if (_10) {
        if (auto* source = _10->getXLink())
            sub_7100EC56D8(source, request);
    }
    user->emit(locator, handle);
    if (!handle->isActive() || !request->_b8)
        return;
    auto* actor = request->_b8;
    auto* model = actor->getModel();
    if (!model || !model->getUnits()[0]->mModelUnit) {
        handle->setPosition(actor->getMtx().getTranslation());
    } else if (actor->getName() == "Enemy_Keese" && request->_90 == 0x1b) {
        handle->setPosition(request->mtx.getTranslation());
    } else {
        handle->setPosition(*actor->getModel()->getUnits()[0]->mModelUnit->get50());
    }
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
        snd::ExpressionSoundCtrl::instance()->sub_710104FA78(*handle);
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: the unused size-calculator receiver and size temporary are removed.
void Reaction::Unk1::sub_7100EC6C00(Actor* actor, const sead::Vector3f& position) {
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.enableLayer(phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(phys::ContactLayer::EntityGroundRough);
    sead::Vector3f start = position;
    start.y += 0.2f;
    query.setStartAndDisplacement(start, sead::Vector3f::ey * -0.4f);
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return;
    const auto& mask = query.getMaterialMask();
    const bool stone_bottom = mask.getMaterial() == phys::Material::Water &&
        sead::SafeString(mask.getSubMaterialName()) == "Water_StoneBottom";
    sub_7100EC696C(10.0f, actor, position, stone_bottom, true);
    if (mask.getMaterial() == phys::Material::GrudgeSlow) {
        const s32 size = Reaction::instance()->sub_7100EC2278(actor, nullptr);
        sub_7100EC5C40(-6.0f, 0.1f, actor, position, size, 1, &mask);
    }
}

}  // namespace ksys::act

namespace ksys::act {

// 0x7100ec86f4 (placeholder name): sets the event position of `handle`, then applies the volume and
// pitch scales computed by sub_7100EC7D50. The results are not used here.
void Reaction::Unk1::sub_7100EC86F4(xlink2::HandleSLink* handle, const sead::Vector3f& position, f32 a,
                                   f32 b, f32 c, f32 d) {
    if (!handle)
        return;
    handle->setPosition(position);
    f32 volume = 0.0f;
    f32 pitch = 1.0f;
    sub_7100EC7D50(a, b, c, d, handle, &volume, &pitch);
}

}  // namespace ksys::act

namespace {

struct RollDragSize {
    const char* name;
    f32 limit;
};

}  // namespace

// 0x71024efef8: the roll-drag asset of each size class and its speed limit.
KSYS_VISIBILITY_HIDDEN const RollDragSize sRollDragSizes[6] = {
    {"CmnObj_Base_TinySize_RollDrag", 5.0f},
    {"CmnObj_Base_SmallSize_RollDrag", 50.0f},
    {"CmnObj_Base_HalfSize_RollDrag", 300.0f},
    {"CmnObj_Base_NormalSize_RollDrag", 1000.0f},
    {"CmnObj_Base_DoubleSize_RollDrag", 3000.0f},
    {"CmnObj_Base_GiantSize_RollDrag", 20000.0f},
};

namespace ksys::act {

// NON_MATCHING: the original evaluates the asset name before the handle argument (ours passes the
// handle first) and adds the table's low address bits one slot later; every value is the same.
// 0x7100ec7edc (placeholder name): emits the roll-drag asset of the size class for `speed` and
// returns whether the handle is active afterwards.
bool Reaction::Unk1::sub_7100EC7EDC(f32 speed, xlink2::HandleSLink* handle) {
    if (speed > sRollDragSizes[0].limit) {
        s32 size = 0;
        if (speed > sRollDragSizes[5].limit)
            size = 5;
        else if (speed > sRollDragSizes[4].limit)
            size = 4;
        else if (speed > sRollDragSizes[3].limit)
            size = 3;
        else if (speed > sRollDragSizes[2].limit)
            size = 2;
        else if (speed > sRollDragSizes[1].limit)
            size = 1;

        eft::sub_710105DDB8(_8, sRollDragSizes[size].name, handle);
        return handle->isActive();
    }
    return false;
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: the original tests the material before the flag in the wetness check; ours hoists
// the flag test. The values and the branch targets are the same.
// 0x7100ec7aa0 (placeholder name): sets the material properties and the wetness property of the
// actor's effect link from the material mask, and returns whether the link has an event.
bool Reaction::Unk1::sub_7100EC7AA0(const phys::MaterialMask& mask, s32 flag, f32 value) {
    if (!_8)
        return false;
    auto* xlink = _8->getXLink();
    if (!xlink)
        return false;
    auto* user = xlink->_50;
    if (!user)
        return false;

    const int material = mask.getMaterial();
    user->setPropertyValue(0, material);
    const int sub_material = mask.getSubMaterialIdx();
    user->setPropertyValue(1,
                           ksys::xlink::Manager::instance()->getSubMaterialIndex(material, sub_material));
    user->setPropertyValue(4, value);

    f32 wetness = 0.0f;
    if (material == 8)
        wetness = 1.0f;
    if (material != 8) {
        if (!(flag & 1))
            wetness = ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_2d0;
    }
    user->setPropertyValue(7, wetness);
    return true;
}

// NON_MATCHING: volume setter stores retain the existing library order.
void Reaction::Unk1::sub_7100EC7B90(f32 a, f32, f32, f32 d, f32 e, f32 f, f32 g,
                                    xlink2::HandleSLink* handle,
                                    const xlink2::HandleSLink* other, f32* volume, f32* pitch) {
    if (!handle || !handle->isActive())
        return;
    if (d >= 1.0f) {
        handle->setVolumeScale(0.0f);
        handle->setPitchScale(1.0f);
        if (volume)
            *volume = 0.0f;
        if (pitch)
            *pitch = 1.0f;
        return;
    }
    const f32 normalized = sead::Mathf::clampMax(a, 4.0f) * 0.25f;
    f32 volume_scale = (1.0f - d) * (1.0f - d) * (normalized * normalized * f);
    if (other && other->isActive()) {
        const auto* event = static_cast<const xlink2::EventSLink*>(other->getEvent());
        volume_scale *= (1.0f - event->getVolumeScale()) * 0.6f + 0.4f;
    }
    handle->setVolumeScale(sead::Mathf::clampMin(volume_scale, 0.0f));
    const f32 lpf_scale = e < 15.0f ? (e / -15.0f + 1.0f) * 0.75f : 0.0f;
    handle->setPitchScale(sead::Mathf::clampMin(g, 0.0f));
    handle->setLpfScale(lpf_scale);
    if (volume)
        *volume = volume_scale;
    if (pitch)
        *pitch = g;
}

// NON_MATCHING: volume setter stores retain the existing library order.
void Reaction::Unk1::sub_7100EC7D50(f32 a, f32 b, f32 c, f32 d,
                                    xlink2::HandleSLink* handle, f32* volume, f32* pitch) {
    if (!handle)
        return;
    if (b >= 1.0f) {
        handle->setVolumeScale(0.0f);
        handle->setPitchScale(1.0f);
        if (volume)
            *volume = 0.0f;
        if (pitch)
            *pitch = 1.0f;
        return;
    }
    f32 volume_scale = 0.0f;
    f32 pitch_scale = 1.0f;
    if (a >= 0.0f) {
        const f32 normalized = sead::Mathf::clamp(a / 3.0f, 0.0f, 1.0f);
        volume_scale = (1.0f - b) * (1.0f - b) * (normalized * normalized * c);
        pitch_scale = (normalized * 0.1f + 0.95f) * d;
    }
    handle->setVolumeScale(sead::Mathf::clampMin(volume_scale, 0.0f));
    handle->setPitchScale(sead::Mathf::clampMin(pitch_scale, 0.0f));
    if (volume)
        *volume = volume_scale;
    if (pitch)
        *pitch = pitch_scale;
}

}  // namespace ksys::act
