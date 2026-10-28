#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Effect/eftAmbientEffect.h"
#include "Game/Actor/actCamera.h"
#include "Game/Scene/gameScene.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysParticleMgr.h>
#include <nn/vfx/Resource.h>
#include <ptcl/seadPtclSystem.h>
#include <cstring>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameGraphics.h"
#include "Game/gameStage.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkUser.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include <resource/seadResource.h>
#include <xlink2/xlink2SystemELink.h>
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

void Effect::loadELinkDatabase(const sead::SafeString& requester) {
    res::LoadRequest req;
    req.mRequester = requester;
    auto* res = sead::DynamicCast<sead::DirectResource>(
        mELinkDBHandle.load("ELink2/ELink2DB.belnk", &req, nullptr));
    xlink2::SystemELink::instance()->loadResource(res->getRawData());
}

void Effect::initBeforeStageGen(sead::Heap* heap) {
    _9b98 = true;
    _9b9c = 0;
    _2a42c = 0;
    clearFlags(0x1180);
    setFlags(0x180);
    initParticleGroups(true);
    _9fe0.sub_7100DA2118();
    mAmbientEffectMgr->reset();
    mRainbow.start();
    // NON_MATCHING: the original (C++14) constructs the CreateArg before evaluating instance(), so
    // our C++17 build keeps the instance in a register and the body is one load longer.
    mUserInstance = xlink2::SystemELink::instance()->createUserInstance(
        xlink2::UserInstance::CreateArg("UI", &ksys::xlink::sUnk_7102652e70), heap, 0);
    mUserInstance->setupResource(heap);
    mUserInstance->setIsActive(true);
    mWindStatsMaybe = uking::StatisticsMgr::instance()->getStatsPointer("terrain_is_in_door");
    mForestDensityStats = uking::StatisticsMgr::instance()->getStatsPointer("forest_density");
    _9b8c = 0;
    _9b8d = 0;
    _9b90 = 4.0f;
    _9b94 = 0.0f;
}

void Effect::initParticleGroups(bool flag) {    Graphics::instance()->mModelScenes[0]->clearParticleGroup(-1);
    if (flag) {
        Graphics::instance()->mModelScenes[0]->addParticleGroup(0, -1);
        Graphics::instance()->mModelScenes[0]->addParticleGroup(1, -1);
        Graphics::instance()->mModelScenes[0]->addParticleGroup(2, -1);
        Graphics::instance()->mModelScenes[0]->addParticleGroup(0x3e, -1);
        if (!_9ba0)
            Graphics::instance()->mModelScenes[0]->addParticleGroup(3, -1);
    }
    gsys::ParticleMgr::instance()->get_68().setBit(2);
    Graphics::instance()->mModelScenes[1]->clearParticleGroup(-1);
    Graphics::instance()->mModelScenes[1]->addParticleGroup(0x3e, -1);
}

// NON_MATCHING: the compiler shrink-wraps the frame and selects the failed-query result.
f32 Effect::queryForestDensity(const sead::Vector3f* position) {
    // The zero initialiser is what keeps the frame live across the manager null check in the
    // original (its prologue is not shrink-wrapped).
    f32 value = 0.0f;
    auto* mgr = uking::StatisticsMgr::instance();
    if (mgr && mgr->query(&value, 1, mForestDensityStats, position))
        return value;
    return 0.0f;
}
// 0x71011b3e84 (placeholder name): the effect-level scale curve Effect::init fills at +0x2a3e0.
f32 Effect::getLevelScaleMaybe(f32 level) const {
    const s32 index = s32(level);
    if (index < 0)
        return 0.0f;
    if (index >= 15)
        return mLevelScaleTable[15];
    const f32 t = level - static_cast<f32>(index);
    const f32 lo = mLevelScaleTable[index];
    const f32 hi = mLevelScaleTable[index + 1];
    return lo + t * (hi - lo);
}

// 0x71011b2ee0 (slot m13): xlink asks us for the emitter set to use for a DummyBlank replacement.
// Scans resource slots 0..9 and the demo resource ids 10..41; the dummy-blank name takes a set
// that does not need a fade, the dummy-blank-loop name one that does.
// NON_MATCHING: only the two condition blocks differ: clang merges the two error tests into one
// inverted-or form and orders them differently (5 instructions). Registers, calls and the loop
// agree.
void Effect::replaceResEset(Unk_ResEset* eset, const xlink2::ResAssetCallTable& table,
                            const xlink2::ResourceAccessorELink& accessor, const char* name) {
    if (!(mFlags & cFlag_Unk2000))
        return;

    const int dummy_blank = std::strcmp(name, "DummyBlank");
    const int dummy_blank_loop = std::strcmp(name, "DummyBlankLoop");
    if (dummy_blank != 0 && dummy_blank_loop != 0)
        return;

    const char* resource_name = accessor.getCustomParamValueString(11, table);
    auto* system = gsys::ParticleMgr::instance()->getSystem();
    for (s32 i = 0; i < 42; ++i) {
        s32 resource_id;
        if (i < 10)
            resource_id = i;
        else
            resource_id = mDemoResourceIds[i - 10];
        if (resource_id == -1)
            continue;

        auto* resource = system->GetResourceMaybe(resource_id);
        if (!resource || !resource->IsAvailableMaybe())
            continue;

        const s32 eset_id = system->SearchEmitterSetId(resource_name, resource_id);
        if (eset_id < 0)
            continue;

        const bool need_fade = resource->IsNeedFade(eset_id);
        if (dummy_blank == 0) {
            if (need_fade) {
                if (!xlink2::SystemELink::instance()->isServerConnecting())
                    sead::FormatFixedSafeString<128> message(
                        "EFT_ERR[System::replaceResEset_NeedLoop](%s)", resource_name);
                return;
            }
        }
        if (!(need_fade || dummy_blank_loop != 0)) {
            if (!xlink2::SystemELink::instance()->isServerConnecting())
                sead::FormatFixedSafeString<128> message(
                    "EFT_ERR[System::replaceResEset_NeedLoop](%s)", resource_name);
            return;
        }

        eset->_0 = u16(resource_id);
        eset->_2 = u16(eset_id);
        return;
    }

    if (!xlink2::SystemELink::instance()->isServerConnecting())
        sead::FormatFixedSafeString<128> message("EFT_ERR[System::replaceResEset](%s)",
                                                 resource_name);
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

void Effect::calc() {
    if (_96b0)
        return;
    if (getSceneStatus())
        return;
    if (!_192c8)
        return;
    if (!_9b98)
        return;
    // The original reads the flag through the singleton instance here, not through `this`.
    if (Effect::instance()->mFlags & cFlag_Unk2000)
        return;
    if (!_9fc0)
        return;
    if (!_9fc0->m148())
        return;
    mAmbientEffectMgr->calc(this);
}


// NON_MATCHING: the final bit test becomes cset instead of the original's orr/branch pair (4 bytes shorter).
bool Effect::sub_71011B7DA0(const sead::Vector3f* wind) {
    if (!_9b98 || !_192c8)
        return false;
    auto* stats = uking::StatisticsMgr::instance();
    if (!stats)
        return false;
    u32 mask;
    if (stats->sub_7100E33EA0(&mask, 1, mWindStatsMaybe, wind) == 0)
        return false;

    f32 a = 0.0f;
    if (sead::Mathf::abs(wind->x) > 1.1920929e-06f)
        a = wind->x / 5.0f;
    f32 b = 0.0f;
    if (sead::Mathf::abs(wind->z) > 1.1920929e-06f)
        b = wind->z / 5.0f;

    const s32 fa = sead::Mathf::floor(a);
    const s32 fb = sead::Mathf::floor(b);
    const u32 ia = u32((a - f32(fa)) * 5.0f);
    const u32 ib = u32((b - f32(fb)) * 5.0f);
    const u32 bit = 1u << (ib * 5 + ia);
    if (bit & mask)
        return true;
    return false;
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

// NON_MATCHING: the setBit `orr` has its operands swapped (sead::LongBitFlag::setBit in lib).
void Effect::sub_71011B8584(bool on) {
    const bool flag = _96b1;
    _96b0 = on;
    gsys::ParticleMgr::instance()->set_90(on);
    initParticleGroups(flag);
    if (on)
        ++_193e8;
    else
        _193e8 = 0;
    for (u32 i = 0; i < 61; ++i)
        gsys::ParticleMgr::instance()->get_58().changeBit(i, !on);
}

// NON_MATCHING: the setBit `orr` has its operands swapped (sead::LongBitFlag::setBit in lib).
void Effect::sub_71011B8658(bool on) {
    const bool flag = _96b0;
    _96b1 = on;
    gsys::ParticleMgr::instance()->set_90(flag);
    initParticleGroups(on);
    if (flag)
        ++_193e8;
    else
        _193e8 = 0;
    for (u32 i = 0; i < 61; ++i)
        gsys::ParticleMgr::instance()->get_58().changeBit(i, !flag);
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
