#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Effect/eftAmbientEffect.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/XLink/xlinkManager.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include <gsys/gsysParticleMgr.h>
#include <nn/vfx/Resource.h>
#include <ptcl/seadPtclSystem.h>
#include <cmath>
#include <cstring>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameGraphics.h"
#include "Game/gameStage.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Camera/CameraMgr.h"
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
    // C++14 evaluation order: the original constructs the CreateArg before evaluating instance().
    {
        xlink2::UserInstance::CreateArg arg("UI", &ksys::xlink::sUnk_7102652e70);
        mUserInstance = xlink2::SystemELink::instance()->createUserInstance(arg, heap, 0);
    }
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

// 0x71011b68b0 (placeholder name; declared only): the camera-relative wind effect of the 0x40-byte
// object at Effect +0x19330 (reads the camera actor at Effect +0x9fc0).
void sub_71011B68B0(u8* self, Effect* effect);

// 0x71011b6ff8: steps the water-effect placement ring around the camera. It samples the
// water_distance statistics at the camera, checks the terrain material on a circle around the
// camera and ray casts down to find the water surface; the state selects the effect.
// NON_MATCHING: the Material out local's constructor store and the temporary stack slots differ;
// the distance limit also stays a compare against 60 rather than the original's 59 / b.hi.
void Effect::x_0() {
    auto* statistics = uking::StatisticsMgr::instance();
    if (!statistics)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    if (!_192c8)
        return;
    if (!map::PlacementMgr::instance())
        return;

    void* water_distance = statistics->getStatsPointer("water_distance");
    const sead::Vector3f camera_pos = camera->getPos();
    mWaterRingDistance = 9999.0f;
    f32 depth;
    bool valid = statistics->query(&depth, 1, water_distance, &camera_pos);
    s32 scaled = 0;
    if (valid) {
        scaled = s32(depth * -0.9f);
        mWaterRingDistance = f32(u32(scaled));
        valid = u32(scaled) <= 59;
    }
    if (!valid) {
        mWaterRingState = 0;
        mWaterRingTimer = 0.0f;
        return;
    }

    if (mWaterRingTimer >= 0.0f)
        mWaterRingTimer -= 0.04f;
    else
        mWaterRingState = 0;

    tera::System* system = map::PlacementMgr::instance()->mTeraSystem;
    if (!system || !system->_8)
        return;

    f32 angle = mWaterRingAngle + 0.20943952f;
    if (angle > 6.2831855f)
        angle = 0.0f;
    mWaterRingAngle = angle;

    const f32 radius =
        f32(u32(scaled)) + 15.0f + sead::GlobalRandom::instance()->getF32() * 35.0f;
    sead::Vector2f xz;
    xz.x = camera_pos.x + std::sin(mWaterRingAngle) * radius;
    xz.y = camera_pos.z + std::cos(mWaterRingAngle) * radius;

    phys::Material material;
    s32 submaterial;
    if (!tera::sub_710110B6A4(&material, &submaterial, &xz, system))
        return;

    const bool special = (material == phys::Material::Water && submaterial >= 1 &&
                          submaterial <= 3) ||
                         material == phys::Material::Lava || material == phys::Material::Bog;
    if (!special) {
        if (material != phys::Material::Water)
            return;
        if (mWaterRingTimer >= 0.0f)
            return;
        mWaterRingState = 5;
        return;
    }

    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.enableLayer(phys::ContactLayer::EntityGroundRough);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    const sead::Vector3f base(xz.x, camera_pos.y, xz.y);
    sead::Vector3f position = base + sead::Vector3f(0.0f, 600.0f, 0.0f);
    query.setStart(position);
    position = base + sead::Vector3f(0.0f, -600.0f, 0.0f);
    query.setEnd(position);
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return;

    const phys::Material hit_material = query.getMaterialMask().getMaterial();
    if (hit_material == material) {
        bool hit = true;
        if (hit_material == phys::Material::Water && submaterial == 3)
            mWaterRingState = 2;
        else if (hit_material == phys::Material::Water && submaterial == 2)
            mWaterRingState = 6;
        else if (hit_material == phys::Material::Water && submaterial == 1)
            mWaterRingState = 4;
        else if (hit_material == phys::Material::Lava)
            mWaterRingState = 3;
        else if (hit_material == phys::Material::Bog)
            mWaterRingState = 1;
        else
            hit = false;
        if (hit)
            mWaterRingTimer = 15.0f;
    }

    // The hit position is only evaluated for the debug flag; the result is not used.
    if (hasFlags(0x4))
        query.getHitPosition(&position);
}

// 0x71011b742c: probes the terrain / height-map heights along the camera's horizontal direction
// (rotated left or right on alternating frames) and at the player, and keeps the distance at
// which the water effect can start.
// NON_MATCHING: the vector / height temporaries get different stack slots (frame 0x10 larger) and
// the rotated direction and index live in different registers; the height probes themselves match.
void Effect::x_1() {
    mWaterDistanceMaybe = 25.0f;
    if (hasFlags(0x4000))
        return;
    auto* placement_mgr = map::PlacementMgr::instance();
    if (!placement_mgr)
        return;
    tera::System* system = placement_mgr->mTeraSystem;
    if (!system)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;

    const sead::Vector3f pos = camera->getPos();
    const sead::Vector3f at = camera->getAt();
    sead::Vector3f dir{at.x - pos.x, 0.0f, at.z - pos.z};
    dir.normalize();

    if (hasFlags(0x8000))
        return;

    const sead::Vector3f up = camera->getUp();
    const sead::Vector3f cross = dir.cross(up);
    const u32 index = mWaterDirIndex;
    mWaterDirIndex = index > 1 ? 0 : index + 1;

    sead::Vector3f rotated = dir;
    if (index == 2)
        rotated = dir * 2.0503037f - cross;
    else if (index == 1)
        rotated = dir * 2.0503037f + cross;
    rotated.normalize();

    const s32 dir_index = s32(index);
    f32& dist = mWaterDirDistances[dir_index];
    const sead::Vector3f full(pos.x + rotated.x * dist, pos.y + rotated.y * dist - 1.5f,
                              pos.z + rotated.z * dist);
    const sead::Vector3f half = pos + (full - pos) * 0.5f;
    const sead::Vector2f full_xz(full.x, full.z);
    const sead::Vector2f half_xz(half.x, half.z);

    f32 graphics_full = 0.0f;
    f32 graphics_half = 0.0f;
    Graphics::instance()->getUnk_ab0()->sub_7100F29EB4(&graphics_full, full_xz);
    Graphics::instance()->getUnk_ab0()->sub_7100F29EB4(&graphics_half, half_xz);

    f32 terrain_full;
    f32 terrain_half;
    tera::sub_71011094A0(&terrain_full, &full_xz, system, -1, 0);
    tera::sub_71011094A0(&terrain_half, &half_xz, system, -1, 0);

    f32 target = 32.0f;
    if (graphics_full > (terrain_full > full.y ? terrain_full : full.y) + 2.5f ||
        graphics_half > (terrain_half > half.y ? terrain_half : half.y) + 2.5f)
        target = 5.0f;

    dist += (target - dist) * 0.2f;

    f32 value = mWaterDistanceMaybe;
    for (s32 i = 0; i < 3; ++i) {
        const f32 limit = mWaterDirDistances[i] - 7.0f;
        if (value > limit) {
            mWaterDistanceMaybe = limit;
            value = limit;
        }
        if (value > 25.0f) {
            value = 25.0f;
            mWaterDistanceMaybe = 25.0f;
        }
    }

    if (_9fb8) {
        auto* player = _9fb8->getPlayer();
        const sead::Vector3f player_pos = player->getMtx().getTranslation();
        const f32 t = mPlayerWaterDistance;
        const sead::Vector3f point(player_pos.x + rotated.x * t,
                                   player_pos.y + rotated.y * t + 1.0f,
                                   player_pos.z + rotated.z * t);
        const sead::Vector2f point_xz(point.x, point.z);

        f32 graphics_height = 0.0f;
        f32 terrain_height;
        Graphics::instance()->getUnk_ab0()->sub_7100F29EB4(&graphics_height, point_xz);
        tera::sub_71011094A0(&terrain_height, &point_xz, system, -1, 0);

        const f32 height = point.y > terrain_height + 0.5f ? point.y : terrain_height + 0.5f;
        const f32 new_dist = graphics_height > height ? 1.0f : 10.0f;
        mPlayerWaterDistance += (new_dist - mPlayerWaterDistance) * 0.2f;

        if (mPlayerWaterDistance < 9.5f) {
            const sead::Vector3f probe(point.x, height, point.z);
            const f32 limit = (probe - pos).length() * 0.9f - 5.0f;
            if (limit < mWaterDistanceMaybe)
                mWaterDistanceMaybe = limit;
        }
    }
}

// 0x71011b6b48: kills the pending effect handles, samples the forest_density statistics at four
// points along the camera direction (5, 25, 35 and -5 units), clamps the density by the effect
// level and the terrain under the camera, then keeps Effect +0x192b0 in 0..1.
// NON_MATCHING: the probe vector gets a different stack slot (the frame is 0x10 larger) and the
// query argument setup is scheduled around the call differently; the arithmetic and branches match.
void Effect::calcGsysParallel() {
    for (s32 i = 0; i < 32; ++i) {
        auto& entry = _9fe0._0[i];
        if (!entry.actor && entry._28) {
            entry._28 = false;
            entry.handle.kill();
        }
    }

    auto* statistics = uking::StatisticsMgr::instance();
    if (!statistics)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;

    const sead::Vector3f pos = camera->getPos();
    const sead::Vector3f at = camera->getAt();
    sead::Vector3f dir{at.x - pos.x, at.y - pos.y, at.z - pos.z};
    dir.normalize();

    f32 height5;
    f32 height25;
    f32 height35;
    f32 heightNeg5;
    sead::Vector3f probe = pos + dir * 5.0f;
    f32 count = u32(statistics->query(&height5, 1, mForestDensityStats, &probe));
    probe = pos + dir * 25.0f;
    count += u32(statistics->query(&height25, 1, mForestDensityStats, &probe));
    probe = pos + dir * 15.0f + dir * 20.0f;
    count += u32(statistics->query(&height35, 1, mForestDensityStats, &probe));
    probe = pos + dir * 15.0f - dir * 20.0f;
    count += u32(statistics->query(&heightNeg5, 1, mForestDensityStats, &probe));

    if (count == 4.0f) {
        const f32 sum = height5 + height25 + height35 + heightNeg5;
        if (sead::Mathf::isNan(sum)) {
            sead::FormatFixedSafeString<128> message("EFT_ERR[System::calcGsysParallel]");
        } else {
            f32 value = sum;
            const s32 level = _9fe0.mCount;
            if (level == 2) {
                if (value > 0.6f)
                    value = 0.6f;
            } else if (level == 1) {
                if (value > 0.5f)
                    value = 0.5f;
            } else if (level == 0 && value > 0.4f) {
                value = 0.4f;
            }
            _192b0 += (value - _192b0) * 0.1f;
        }
    }

    auto* placement_mgr = map::PlacementMgr::instance();
    if (placement_mgr && placement_mgr->mTeraSystem) {
        f32 height = -9999.0f;
        if (Graphics::instance()->getMapStateMaybe() < 2) {
            const sead::Vector2f xz(pos.x, pos.z);
            tera::sub_71011094A0(&height, &xz, placement_mgr->mTeraSystem, -1, 0);
        }
        const f32 diff = pos.y - height;
        if (diff > 10.0f)
            _192b0 = ((diff - 10.0f) / -7.0f + 1.0f) * _192b0;
    }

    if (_192b0 < 0.0f)
        _192b0 = 0.0f;
    else if (_192b0 > 1.0f)
        _192b0 = 1.0f;
}

// 0x71011b7b0c: when the scene is not ready, step the parallel / camera effect state, then run the
// player water grid and the xlink calculation.
// NON_MATCHING: our clang deletes the PtrArray bounds check before mMgrs[3] (it loads from the null
// the check returns, so the check counts as dead); the image keeps it. Same toolchain limitation as
// the s161 PtrArray HARD entry. Everything else matches.
void Effect::calcMostProbably2() {
    if (!_9b98)
        return;
    if (!_96b0 && !getSceneStatus()) {
        if (_192c8) {
            calcGsysParallel();
            x_0();
            x_1();
            sub_71011B68B0(_19330, this);
            const f32 delta = VFR::instance()->getDeltaFrame();
            auto* wm = world::Manager::instance();
            if (wm) {
                const f32 weather = static_cast<world::WeatherMgr*>(wm->getMgrMaybe(3))->mTransition._2dc;
                const bool weather_zero = world::WeatherMgr::x_7();
                // 1 / 1800 as a float.
                const f32 rate = delta * 0.0005555556f;
                f32 value = _192b4;
                if (weather > 0.0f && !weather_zero) {
                    value += rate;
                    _192b4 = value;
                    if (value > 1.0f)
                        _192b4 = 1.0f;
                } else {
                    value -= rate;
                    _192b4 = value;
                    if (value < 0.0f)
                        _192b4 = 0.0f;
                }
            }
        } else {
            _192b0 = 1.0f;
            _192b4 = 0.0f;
        }
    }

    if ((mFlags & cFlag_Unk2000000) && _9fb8) {
        auto* player = _9fb8->getPlayer();
        const sead::Vector3f pos = player->getMtx().getTranslation();
        for (s32 x = -16; x < 16; ++x) {
            for (s32 z = -16; z < 16; ++z) {
                sead::Vector3f wind = pos + sead::Vector3f(x * 0.5f, 0.0f, z * 0.5f);
                sub_71011B7DA0(&wind);
                f32 height = 0.0f;
                sub_71011B2A34(&wind, nullptr, &height, nullptr, nullptr, nullptr, true);
            }
        }
    }

    if (xlink2::SystemELink::instance()->isServerConnecting()) {
        xlink::Manager::instance()->getResourceLock().lock();
        xlink2::SystemELink::instance()->calc();
        xlink::Manager::instance()->getResourceLock().unlock();
    } else {
        xlink2::SystemELink::instance()->calc();
    }
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

// NON_MATCHING: the two matrix copies match (three 16-byte rows), but clang hoists the ParticleMgr
// chain above the mFlags bit 3 test (the original keeps it in each arm) and colours registers
// differently.
void Effect::updatePlayerPos(const sead::Matrix34f& matrix, const sead::Matrix34f& alternate) {
    const u32 flags = mFlags;
    if (flags & 8) {
        auto& camera = gsys::ParticleMgr::instance()->getSystem()->getCameraMatrix();
        sead::Matrix34CalcCommon<f32>::copy(camera, sead::Matrix34f::ident);
        return;
    }
    auto& camera = gsys::ParticleMgr::instance()->getSystem()->getCameraMatrix();
    if (flags & 0x10)
        sead::Matrix34CalcCommon<f32>::copy(camera, alternate);
    else
        sead::Matrix34CalcCommon<f32>::copy(camera, matrix);
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

// NON_MATCHING: the material local spills before the bit test instead of after it and the shift uses
// different registers (w10 / w11 vs the original w9 / w10).
bool Effect::sub_71011B2D34(const sead::Vector3f* pos, f32* out_height,
                            phys::Material* out_material, s32* out_submaterial,
                            sead::Vector3f* out_normal) {
    if (out_height)
        *out_height = -99999.0f;

    sead::Vector3f hit;
    sead::Vector3f normal;

    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityWater);
    query.enableLayer(phys::ContactLayer::EntityGroundRough);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.setStart(*pos + sead::Vector3f(0.0f, 1.0f, 0.0f));
    query.setEnd(*pos + sead::Vector3f(0.0f, -600.0f, 0.0f));
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return false;

    query.getHitPosition(&hit);
    query.getHitNormal(&normal);

    const phys::Material material = query.getMaterialMask().getMaterial();
    switch (material) {
    case phys::Material::Water:
    case phys::Material::Lava:
    case phys::Material::Bog:
        break;
    default:
        return false;
    }

    if (out_height)
        *out_height = hit.y;
    if (out_material && out_submaterial) {
        *out_material = material;
        *out_submaterial = query.getMaterialMask().getSubMaterialIdx();
    }
    if (out_normal)
        *out_normal = query.getHitNormalInline();
    return true;
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
