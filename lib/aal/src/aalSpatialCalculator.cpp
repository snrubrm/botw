#include "aal/aalSpatialCalculator.h"
#include <cstring>
#include <prim/seadScopedLock.h>
#include "aal/aalCone.h"
#include "aal/aalShape.h"

namespace aal {

// NON_MATCHING: same stores, but the original issues them in a different order (it stores flags, matrix, velocity,
// attenuator, _2a, user_param, then the zeroed float/shape block).
// 0x7100b8f4ec
void SpatialCalculator::Setting::initialize() {
    flags = 0xd;
    actor_matrix = nullptr;
    velocity = nullptr;
    attenuator = nullptr;
    _2a = 0xffff;
    user_param = 0;
    doppler_factor = 0.0f;
    sound_source_size = 0.0f;
    shape = nullptr;
}

// 0x7100b8f5a0 (D2) / 0x7100b8f684 (D0)
SpatialCalculator::~SpatialCalculator() {
    finalize();
}

// 0x7100b8f61c
void SpatialCalculator::finalize() {
    if (!mInitialized)
        return;

    if (mCone) {
        ConeFactory::instance()->destroy(mCone);
        mCone = nullptr;
    }
    if (mResults) {
        delete[] mResults;
        mResults = nullptr;
        mResultNum = 0;
    }
    if (mSetting.shape)
        mSetting.shape->detachSpatialCalculator_(this);
    mInitialized = false;
}

// 0x7100b8f930
bool SpatialCalculator::detachShape(bool reset_position) {
    if (!mSetting.shape)
        return false;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mSetting.shape->detachSpatialCalculator_(this);
    mSetting.shape = nullptr;
    if (reset_position)
        detachPositioningInfo();
    return true;
}

// 0x7100b8fb00
s32 SpatialCalculator::getResultNum() const {
    if (mResults)
        return mResultNum;
    return 0;
}

// 0x7100b8fab8
const SpatialCalculator::Result* SpatialCalculator::getResult(s32 index) const {
    const Result* result = nullptr;
    if (index >= 0 && mResults && mResultNum > index) {
        if (static_cast<u32>(index) < static_cast<u32>(mResultNum))
            result = &mResults[index];
    }
    return result;
}

// 0x7100b8fe28
void SpatialCalculator::beginReferred() {
    ++mReferredCount;
}

// 0x7100b8fe38
void SpatialCalculator::endReferred() {
    if (mReferredCount - 1 >= 0)
        --mReferredCount;
}

// 0x7100b8fe4c
bool SpatialCalculator::isReferred() const {
    return mReferredCount != 0;
}

// 0x7100b8fe5c
bool SpatialCalculator::hasSetting(const Setting& setting) const {
    return std::memcmp(&mSetting, &setting, sizeof(Setting)) == 0;
}

// 0x7100b8f900
void SpatialCalculator::detachPositioningInfo() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mSetting.actor_matrix = nullptr;
    mSetting.velocity = nullptr;
}

}  // namespace aal
