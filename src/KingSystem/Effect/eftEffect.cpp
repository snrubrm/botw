#include "KingSystem/Effect/eftEffect.h"
#include "Game/Actor/actCamera.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysParticleMgr.h>
#include <ptcl/seadPtclSystem.h>
#include <cstring>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameStage.h"
#include "Game/gameStatisticsMgr.h"
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

void Effect::debugLog(const char* format, ...) {}

void Effect::initBeforeStageGenB() {
    _9fc8 = 0x1e;
    if (mUserInstance)
        mUserInstance->reset();
}

// NON_MATCHING: the compiler shrink-wraps the frame and selects the failed-query result.
f32 Effect::queryForestDensity(const sead::Vector3f* position) {
    f32 value;
    auto* mgr = uking::StatisticsMgr::instance();
    if (mgr && mgr->query(&value, 1, mForestDensityStats, position))
        return value;
    return 0.0f;
}

// NON_MATCHING: Camera basis calculations use different floating-point register allocation.
void Effect::sub_71011B7930() {
    if (!_192c8 || !_9fc0 || !_9fc0->m148())
        return;
    const auto* event = mFieldEnvEffect.mELink.getEvent();
    if (!event || event->getCreateId() != mFieldEnvEffect.mELink.getCreateId()) {
        xlinkSearchAndEmit(_9fc0->m148(), "FieldEnvEffect", 2, &mFieldEnvEffect);
        return;
    }
    const auto& camera_mtx = _9fc0->m148()->getMtx();
    sead::Vector3f forward(camera_mtx(0, 2), 0.0f, camera_mtx(2, 2));
    forward.normalize();
    const auto up = sead::Vector3f::ey;
    sead::Matrix34f mtx;
    mtx.setBase(0, up.cross(forward));
    mtx.setBase(1, up);
    mtx.setBase(2, forward);
    mtx.setTranslation(_9fc0->m148()->getMtx().getTranslation());
    mFieldEnvEffect.sub_7101241A44(mtx);
}

void Effect::kill_0() {
    gsys::ParticleMgr::instance()->getSystem()->KillAllEmitterSet();
}

void Effect::kill() {
    _9b98 = false;
    gsys::ParticleMgr::instance()->getSystem()->KillAllEmitterSet();
    if (mUserInstance) {
        mUserInstance->destroy();
        mUserInstance = nullptr;
    }
    mRainbow.stop();
    _9fc0 = nullptr;
}

// NON_MATCHING: matrix copies use SIMD loads and stores and identity construction folds.
void Effect::updatePlayerPos(const sead::Matrix34f& matrix, const sead::Matrix34f& alternate) {
    auto& camera = gsys::ParticleMgr::instance()->getSystem()->getCameraMatrix();
    if (mFlags & 8) {
        sead::Matrix34f identity;
        identity.makeIdentity();
        std::memcpy(&camera, identity.a.data(), sizeof(camera));
    } else {
        const auto& source = mFlags & 0x10 ? alternate : matrix;
        std::memcpy(&camera, source.a.data(), sizeof(camera));
    }
}

void Effect::searchAndEmit(const sead::SafeString& name, xlink2::HandleELink* handle) {
    if (!mUserInstance)
        return;
    auto* user = static_cast<xlink2::UserInstanceELink*>(mUserInstance);
    if (handle)
        user->searchAndEmit(name.cstr(), handle);
    else
        user->searchAndEmit(name.cstr());
}

void Effect::addDemoResourceId(u32 id) {
    sead::ScopedLock<sead::CriticalSection> lock(&mDemoResourceCS);
    for (s32 i = 0; i < 32; ++i) {
        if (mDemoResourceIds[i] == -1) {
            mDemoResourceIds[i] = s32(id);
            return;
        }
    }
    // The original builds this debug message before returning.
    sead::FormatFixedSafeString<128> message("EFT_ERR[System::addDemoResourceId]");
}

void Effect::removeDemoResourceId(u32 id) {
    sead::ScopedLock<sead::CriticalSection> lock(&mDemoResourceCS);
    for (s32 i = 0; i < 32; ++i) {
        if (mDemoResourceIds[i] == s32(id)) {
            mDemoResourceIds[i] = -1;
            return;
        }
    }
}

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
