#include "KingSystem/Effect/eftAmbientEffect.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actCamera.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Effect/eftEffect.h"

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
    const f32 angle = mAngle + 0.20943952f;
    mAngle = angle <= 6.2831855f ? angle : 0.0f;
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

}  // namespace ksys::eft
