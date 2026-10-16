#include "KingSystem/Effect/eftEffect.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameStage.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2ResourceAccessor.h>
#include <xlink2/xlink2ResourceAccessorELink.h>

namespace ksys::eft {

SEAD_SINGLETON_DISPOSER_IMPL(Effect)

// NON_MATCHING: the water-disable region test is branchy here (the original evaluates the four bound
// compares together, as in map::sub_7100EDB6E0) and the ray cast vectors sit 8 bytes higher on the stack.
bool Effect::sub_71011B2A34(const sead::Vector3f* pos, f32* out_depth, f32* out_height,
                            phys::Material* material, s32* submaterial, sead::Vector3f* out_normal,
                            bool use_raycast) {
    if (out_depth)
        *out_depth = 0.0f;
    if (out_height)
        *out_height = -99999.0f;

    auto* placement_mgr = map::PlacementMgr::instance();
    if (!placement_mgr)
        return false;
    tera::System* system = placement_mgr->mTeraSystem;
    if (!system)
        return false;

    const sead::Vector2f xz{pos->x, pos->z};
    f32 water_height = -9999.0f;
    f32 terrain_height = -9999.0f;
    tera::sub_71011094A0(&terrain_height, &xz, system, -1, 0);

    if (use_raycast) {
        phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
        query.enableLayer(phys::ContactLayer::EntityWater);
        query.setStart(*pos + sead::Vector3f(0.0f, 1.0f, 0.0f));
        query.setEnd(*pos + sead::Vector3f(0.0f, -600.0f, 0.0f));
        if (query.worldRayCast(phys::ContactLayerType::Entity)) {
            sead::Vector3f hit;
            query.getHitPosition(&hit);
            water_height = hit.y;
            if (out_normal)
                query.getHitNormal(out_normal);
        }
    } else if (!(pos->y <= uking::sTeraWaterDisableHeight &&
                 uking::sTeraWaterDisableBounds.isInside(sead::Vector2f(pos->x, pos->z)))) {
        if (out_normal)
            tera::sub_710110B52C(&water_height, out_normal, &xz, system);
        else
            tera::sub_710110B4A4(&water_height, &xz, system);
    }

    bool has_water;
    if (water_height > terrain_height) {
        if (out_height)
            *out_height = water_height;
        has_water = true;
    } else if ((uking::sUnk_7102606938 - sead::Vector2f(pos->x, pos->z)).length() <
               uking::sMapStaticScale) {
        if (out_height)
            *out_height = water_height;
        has_water = true;
    } else {
        if (out_height)
            *out_height = terrain_height;
        has_water = false;
    }
    if (out_depth)
        *out_depth = water_height - terrain_height;

    if (material && submaterial && !tera::sub_710110B6A4(material, submaterial, &xz, system)) {
        *material = phys::Material::Undefined;
        *submaterial = 0;
    }
    return has_water;
}

void Unk_EffectActorTable::sub_7100DA2118() {
    // NON_MATCHING: SDK range iteration uses a different counter instead of the native paired loop.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mCount = 0;
    for (auto& entry : _0) {
        entry.actor = nullptr;
        entry._28 = false;
    }
}

// NON_MATCHING: iterator unrolling, handle-copy scheduling, and saturating count differ.
bool Unk_EffectActorTable::sub_7100DA216C(act::Actor* actor, const sead::Vector3f& position) {
    static const char* const names[] = {"FallLeaves_A", "FallLeaves_B", "FallLeaves_C", "FallLeaves_D",
                                  "FallLeaves_E"};
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    auto* xlink = actor->getXLink();
    if (!xlink || !xlink->_48)
        return false;
    if (map::PlacementMgr::instance()->mPlacementActors->mStruct1->mFlags.isOn(
            map::PlacementAreaMgr::Flag::LastBoss))
        return false;
    const s32 value = xlink->_48->getResourceAccessor().getUserCustomParamValueInt(0);
    for (auto& entry : _0) {
        if (entry.actor)
            continue;
        entry.actor = actor;
        entry.position = position;
        if (value && act::Reaction::instance()->_28) {
            const char* name = "";
            if (value >= 1 && value <= 5)
                name = names[value - 1];
            entry.handle = searchAndEmitELink(act::Reaction::instance()->_28, name);
            entry.handle.setPosition(position);
            entry._28 = true;
        }
        mCount = sead::Mathi::min(mCount + 1, 32);
        return true;
    }
    return false;
}

bool Unk_EffectActorTable::sub_7100DA2330(act::Actor* actor) {
    // NON_MATCHING: iterator addressing/unrolling and the saturating decrement differ.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& entry : _0) {
        if (entry.actor == actor) {
            entry.actor = nullptr;
            mCount = sead::Mathi::max(mCount - 1, 0);
            return true;
        }
    }
    return false;
}

}  // namespace ksys::eft
