#include "KingSystem/Effect/eftAmbientEffect.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include <prim/seadDelegate.h>
#include "Game/Actor/actCamera.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::eft {

// NON_MATCHING: the compiler retains the handle loop; the original expands its three iterations.
void AmbientEffectEmitter::resetCommon() {
    mHandleIndex = 0;
    for (auto& handle : mHandles) {
        handle.mELink.fade();
        handle.mELink.reset();
    }
    mPending = false;
    mAngle = 0.0f;
    mTimer = 30.0f;
    mInterval = 100.0f;
    mDistance = 30.0f;
    mRadius = 10.0f;
}

// NON_MATCHING: handle bounds checking and cursor update are scheduled differently.
Unk_71012419b4* AmbientEffectEmitter::nextHandle() {
    auto& handle = mHandles[mHandleIndex];
    mHandleIndex = mHandleIndex + 1 < 3 ? mHandleIndex + 1 : 0;
    handle.mELink.fade();
    handle.mELink.reset();
    return &handle;
}

// NON_MATCHING: vector normalization, position stores and floating-point registers differ.
void AmbientEffectEmitter::calcPosition(Effect* effect, sead::Vector3f* output) {
    const auto camera_position = effect->_9fc0->m148()->getMtx().getTranslation();
    mAngle += 0.20943952f;
    if (mAngle > 6.2831855f)
        mAngle = 0.0f;
    const f32 radius = sead::GlobalRandom::instance()->getF32() * mRadius;
    sead::Vector3f player_position = sead::Vector3f::zero;
    if (effect->_9fb8)
        player_position = effect->_9fb8->getPlayer()->getMtx().getTranslation();
    sead::Vector3f direction{player_position.x - camera_position.x, 0.0f,
                            player_position.z - camera_position.z};
    direction.normalize();
    *output = camera_position + direction * mDistance;
    output->x += radius * std::sin(mAngle);
    output->z += radius * std::cos(mAngle);
}

void MothEffectEmitter::reset() {
    resetCommon();
    mInterval = 7.0f;
    mDistance = 25.0f;
    mLightIndex = 0;
}

void SmallFishEffectEmitter::reset() {
    resetCommon();
    mInterval = 20.0f;
    mDistance = 25.0f;
    mRadius = 10.0f;
    mMinWaterDepth = 0.8f;
}

// NON_MATCHING: Material's default constructor initializes the output; depth-result branching differs.
bool SmallFishEffectEmitter::getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                                             sead::Vector3f& output) {
    output = position;
    f32 depth;
    f32 height;
    phys::Material material;
    s32 submaterial;
    const bool valid = effect->sub_71011B2A34(&position, &depth, &height, &material,
                                            &submaterial, nullptr, false) &&
                       material == phys::Material::Water && submaterial == 0 &&
                       depth > mMinWaterDepth;
    output.y = height;
    return valid;
}

void FlyEffectEmitter::reset() {
    resetCommon();
    mInterval = 30.0f;
    mDistance = 20.0f;
    mRadius = 25.0f;
    mMaxWaterDepth = 0.35f;
    mMinForestDensity = 0.09f;
}

// NON_MATCHING: Material's default constructor adds an initialization and changes stack allocation.
bool FlyEffectEmitter::getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                                       sead::Vector3f& output) {
    output = position;
    f32 depth;
    f32 height;
    phys::Material material;
    s32 submaterial;
    const bool valid = effect->sub_71011B2A34(&position, &depth, &height, &material,
                                            &submaterial, nullptr, false) &&
                       material == phys::Material::Water && submaterial == 0 &&
                       depth < mMaxWaterDepth &&
                       effect->queryForestDensity(&position) > mMinForestDensity;
    output.y = height;
    return valid;
}

void ButterflyEffectEmitter::reset() {
    resetCommon();
    mInterval = 30.0f;
    mDistance = 20.0f;
    mRadius = 25.0f;
    mMinFlowers = 1.0f;
}

// NON_MATCHING: the final vector zero stores are ordered differently.
void AmbientEffectRequest::reset() {
    mPosition.set(0.0f, 0.0f, 0.0f);
    mHasPosition = false;
    mHandle.mELink.kill();
    mDistance = 100.0f;
    mPending = false;
    mRequestedPosition.set(0.0f, 0.0f, 0.0f);
}

void AmbientEffectRequest::request(const sead::Vector3f& position) {
    mCS.lock();
    if (mHasPosition && (mPosition - position).length() < mDistance) {
        mCS.unlock();
        return;
    }
    mPending = true;
    mRequestedPosition = position;
    mCS.unlock();
}

void AmbientEffectRequest::calc() {
    mCS.lock();
    if (mPending) {
        mPending = false;
        mHandle.fadeXLink();
        f32 height;
        Effect::instance()->sub_71011B2A34(&mRequestedPosition, nullptr, &height, nullptr,
                                         nullptr, nullptr, true);
        const sead::Vector3f position{mRequestedPosition.x, height, mRequestedPosition.z};
        emit(position);
        mPosition = position;
        mHasPosition = true;
    }
    mCS.unlock();
}

// NON_MATCHING: the two timing resets remain calls instead of being inlined here.
void AmbientEffectMgr::reset() {
    mGoose.reset();
    mLittleBird.reset();
    mMoth.reset();
    mSmallFish.reset();
    mFly.reset();
    mButterfly.reset();
    mFirefly.reset();
    mDragonfly.reset();
    mBlueDragonfly.reset();
    mYellowDragonfly.reset();
}

void FireflyEffectRequest::emit(const sead::Vector3f& position) {
    xlinkSearchAndEmit(act::Reaction::instance()->_28, "Firefly_Dummy", 2, &mHandle);
    mHandle.sub_71012419B4(position);
    mHandle.mELink.setDelayEmitParamF8Flags(6);
}

void DragonflyEffectRequest::emit(const sead::Vector3f& position) {
    xlinkSearchAndEmit(act::Reaction::instance()->_28, "Dragonfly_Dummy", 2, &mHandle);
    mHandle.sub_71012419B4(position);
    mHandle.mELink.setDelayEmitParamF8Flags(6);
}

void BlueDragonflyEffectRequest::emit(const sead::Vector3f& position) {
    xlinkSearchAndEmit(act::Reaction::instance()->_28, "Dragonfly_Blue_Dummy", 2, &mHandle);
    mHandle.sub_71012419B4(position);
    mHandle.mELink.setDelayEmitParamF8Flags(6);
}

void YellowDragonflyEffectRequest::emit(const sead::Vector3f& position) {
    xlinkSearchAndEmit(act::Reaction::instance()->_28, "Dragonfly_Yellow_Dummy", 2, &mHandle);
    mHandle.sub_71012419B4(position);
    mHandle.mELink.setDelayEmitParamF8Flags(6);
}

// NON_MATCHING: the singleton load and stack frame are scheduled differently.
bool ButterflyEffectEmitter::countFlower(map::Unk_71012497f8Entry* entry) {
    const char* name = entry->mName.cstr();
    if (act::InfoData::instance()->hasTag(name, act::tags::UndispCut.getHash()) &&
        sead::SafeString(name).findIndex("Flower") != -1)
        ++mFlowerCount;
    return true;
}

bool ButterflyEffectEmitter::getSpawnPosition(Effect* effect, const sead::Vector3f& position,
                                             sead::Vector3f& output) {
    sead::Vector3f ground_position = position;
    f32 depth;
    f32 height;
    // Return value is discarded in the original; depth output is also supplied there.
    effect->sub_71011B2A34(&position, &depth, &height, nullptr, nullptr, nullptr, false);
    ground_position.y = height;
    output = ground_position;
    auto* mgr = map::PlacementMgr::instance();
    if (!mgr)
        return false;
    sead::Delegate1R<ButterflyEffectEmitter, map::Unk_71012497f8Entry*, bool> callback{
        this, &ButterflyEffectEmitter::countFlower};
    mFlowerCount = 0;
    mgr->sub_71011EB40C(&ground_position, 0.75f, &callback);
    return mFlowerCount >= s32(mMinFlowers);
}

void SmallFishEffectEmitter::calc(Effect* effect) {
    mTimer -= VFR::instance()->getIntervalRatio();
    if (mTimer < 0.0f) {
        mTimer = 0.0f;
        mPending = true;
    } else if (!mPending) {
        return;
    }
    sead::Vector3f candidate;
    sead::Vector3f position;
    calcPosition(effect, &candidate);
    if (getSpawnPosition(effect, candidate, position)) {
        mPending = false;
        mTimer = mInterval * 30.0f;
        auto* handle = nextHandle();
        xlinkSearchAndEmit(act::Reaction::instance()->_28, "SmallFish_Dummy", 2, handle);
        handle->sub_71012419B4(position);
        handle->mELink.setDelayEmitParamF8Flags(6);
    }
    // Native debug-path adjustment remains after emission; do not force its store with volatile.
    if (effect->hasFlags(1u << 19))
        candidate.y += 20.0f;
}

void FlyEffectEmitter::calc(Effect* effect) {
    if (Effect::instance()->hasFlags(1u << 11))
        return;
    mTimer -= VFR::instance()->getIntervalRatio();
    if (mTimer < 0.0f) {
        mTimer = 0.0f;
        mPending = true;
    } else if (!mPending) {
        return;
    }
    sead::Vector3f candidate;
    sead::Vector3f position;
    calcPosition(effect, &candidate);
    if (getSpawnPosition(effect, candidate, position)) {
        mPending = false;
        mTimer = mInterval * 30.0f;
        auto* handle = nextHandle();
        xlinkSearchAndEmit(act::Reaction::instance()->_28, "Fly_Dummy", 2, handle);
        handle->sub_71012419B4(position);
        handle->mELink.setDelayEmitParamF8Flags(6);
    }
    if (effect->hasFlags(1u << 20))
        candidate.y += 20.0f;
}

void ButterflyEffectEmitter::calc(Effect* effect) {
    const f32 temperature = world::Manager::instance()->getTempMgr()->get_3c();
    // Native out-of-range rejection permits unordered temperature; preserve the comparison form.
    if (temperature < 12.0f || temperature > 30.0f)
        return;
    mTimer -= VFR::instance()->getIntervalRatio();
    if (mTimer < 0.0f) {
        mTimer = 0.0f;
        mPending = true;
    } else if (!mPending) {
        return;
    }
    sead::Vector3f candidate;
    sead::Vector3f position;
    calcPosition(effect, &candidate);
    if (getSpawnPosition(effect, candidate, position)) {
        mPending = false;
        mTimer = mInterval * 30.0f;
        auto* handle = nextHandle();
        xlinkSearchAndEmit(act::Reaction::instance()->_28, "Butterfly_Dummy", 2, handle);
        handle->sub_71012419B4(position);
        handle->mELink.setDelayEmitParamF8Flags(6);
    }
    if (effect->hasFlags(1u << 21))
        candidate.y += 20.0f;
}

void Unk_7102512640::calc(Effect* effect) {
    _8 -= VFR::instance()->getIntervalRatio();
    if (_8 < 0.0f) {
        const f32 time = world::Manager::instance()->getTimeMgrUnchecked()->getTime();
        _8 = (_c + (_10 - _c) * sead::GlobalRandom::instance()->getF32()) * 30.0f;
        if (((time >= 75.0f && time < 120.0f) || (time >= 255.0f && time < 300.0f)) &&
            effect->_9fc0 && effect->_9fc0->m148() && effect->_9fc0->m148()->getXLink()) {
            Unk_71012419b4 handle;
            xlinkSearchAndEmit(effect->_9fc0->m148(), "Goose", 2, &handle);
            handle.mELink.setDelayEmitParamF8Flags(6);
        }
    }
}

// NON_MATCHING: camera/position operations and branch layout are scheduled differently.
void Unk_7102512658::calc(Effect* effect) {
    _8 -= VFR::instance()->getIntervalRatio();
    if (_8 < 0.0f) {
        const f32 time = world::Manager::instance()->getTimeMgrUnchecked()->getTime();
        _8 = (_c + (_10 - _c) * sead::GlobalRandom::instance()->getF32()) * 30.0f;
        if (time >= 75.0f && time < 300.0f)
            _14 = true;
    }
    auto* stats = uking::StatisticsMgr::instance();
    if (!stats || !_14 || !effect->_9fc0 || !effect->_9fc0->m148()) {
        _28 = -1.0f;
        return;
    }
    _18 += 0.20943952f;
    if (_18 > 6.2831855f)
        _18 = 0.0f;
    const f32 radius = _1c + _20 * sead::GlobalRandom::instance()->getF32();
    sead::Vector3f position = effect->_9fc0->m148()->getMtx().getTranslation();
    position.x += radius * std::sin(_18);
    position.z += radius * std::cos(_18);
    // Return value is discarded in the original; failure leaves the existing sampled value.
    stats->query(&_28, 1, effect->mForestDensityStats, &position);
    if (!(_28 > _24))
        return;
    auto* placement = map::PlacementMgr::instance();
    const sead::Vector2f xz{position.x, position.z};
    // Terrain query status is discarded in the original, which still supplies y as output.
    tera::sub_71011094A0(&position.y, &xz, placement ? placement->mTeraSystem : nullptr, -1, 0);
    position.y += 5.0f;
    if (!effect->_9fc0 || !effect->_9fc0->m148() || !effect->_9fc0->m148()->getXLink())
        return;
    Unk_71012419b4 handle;
    xlinkSearchAndEmit(act::Reaction::instance()->_28, "LittleBird_A_Dummy", 2, &handle);
    handle.sub_71012419B4(position);
    _14 = false;
    handle.mELink.setDelayEmitParamF8Flags(6);
}

void AmbientEffectMgr::calc(Effect* effect) {
    if (!effect->_9fc0 || !effect->_9fc0->m148())
        return;
    mGoose.calc(effect);
    mLittleBird.calc(effect);
    mMoth.calc(effect);
    mSmallFish.calc(effect);
    if (effect->hasFlags(1u << 19)) {
        const auto player_position = effect->_9fb8->getPlayer()->getMtx().getTranslation();
        for (s32 x = -16; x < 16; ++x) {
            for (s32 z = -16; z < 16; ++z) {
                const sead::Vector3f position{player_position.x + 2.0f * static_cast<f32>(x),
                                              player_position.y + 0.0f,
                                              player_position.z + 2.0f * static_cast<f32>(z)};
                sead::Vector3f output;
                // Called through a pointer in the original (not devirtualised); result discarded.
                (&mSmallFish)->getSpawnPosition(effect, position, output);
            }
        }
    }
    mFly.calc(effect);
    if (effect->hasFlags(1u << 20)) {
        const auto player_position = effect->_9fb8->getPlayer()->getMtx().getTranslation();
        for (s32 x = -16; x < 16; ++x) {
            for (s32 z = -16; z < 16; ++z) {
                const sead::Vector3f position{player_position.x + 2.0f * static_cast<f32>(x),
                                              player_position.y + 0.0f,
                                              player_position.z + 2.0f * static_cast<f32>(z)};
                sead::Vector3f output;
                // Called through a pointer in the original (not devirtualised); result discarded.
                (&mFly)->getSpawnPosition(effect, position, output);
            }
        }
    }
    mButterfly.calc(effect);
    if (effect->hasFlags(1u << 21)) {
        const auto player_position = effect->_9fb8->getPlayer()->getMtx().getTranslation();
        for (s32 x = -16; x < 16; ++x) {
            for (s32 z = -16; z < 16; ++z) {
                const sead::Vector3f position{player_position.x + 2.0f * static_cast<f32>(x),
                                              player_position.y + 0.0f,
                                              player_position.z + 2.0f * static_cast<f32>(z)};
                sead::Vector3f output;
                // Called through a pointer in the original (not devirtualised); result discarded.
                (&mButterfly)->getSpawnPosition(effect, position, output);
            }
        }
    }
    mFirefly.calc();
    if (mFirefly.mHasPosition && effect->_9fc0 && effect->_9fc0->m148()) {
        const auto camera_position = effect->_9fc0->m148()->getMtx().getTranslation();
        if ((mFirefly.mPosition - camera_position).length() > mFirefly.mDistance) {
            mFirefly.mHandle.fadeXLink();
            mFirefly.mHasPosition = false;
        }
    }
    mDragonfly.calc();
    if (mDragonfly.mHasPosition && effect->_9fc0 && effect->_9fc0->m148()) {
        const auto camera_position = effect->_9fc0->m148()->getMtx().getTranslation();
        if ((mDragonfly.mPosition - camera_position).length() > mDragonfly.mDistance) {
            mDragonfly.mHandle.fadeXLink();
            mDragonfly.mHasPosition = false;
        }
    }
    mBlueDragonfly.calc();
    if (mBlueDragonfly.mHasPosition && effect->_9fc0 && effect->_9fc0->m148()) {
        const auto camera_position = effect->_9fc0->m148()->getMtx().getTranslation();
        if ((mBlueDragonfly.mPosition - camera_position).length() > mBlueDragonfly.mDistance) {
            mBlueDragonfly.mHandle.fadeXLink();
            mBlueDragonfly.mHasPosition = false;
        }
    }
    mYellowDragonfly.calc();
    if (mYellowDragonfly.mHasPosition && effect->_9fc0 && effect->_9fc0->m148()) {
        const auto camera_position = effect->_9fc0->m148()->getMtx().getTranslation();
        if ((mYellowDragonfly.mPosition - camera_position).length() > mYellowDragonfly.mDistance) {
            mYellowDragonfly.mHandle.fadeXLink();
            mYellowDragonfly.mHasPosition = false;
        }
    }
}

}  // namespace ksys::eft
