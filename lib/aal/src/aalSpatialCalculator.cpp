#include "aal/aalSpatialCalculator.h"
#include <cstring>
#include <new>
#include <prim/seadScopedLock.h>
#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuationMgr.h"
#include "aal/aalAttenuator.h"
#include "aal/aalCone.h"
#include "aal/aalListener.h"
#include "aal/aalListenerMgr.h"
#include "aal/aalSystemAccessor.h"
#include "aal/aalShape.h"

namespace aal {

// NON_MATCHING: same stores, but the original issues them in a different order (it stores flags, matrix, velocity,
// attenuator, listener_mask, user_param, then the zeroed float/shape block).
// 0x7100b8f4ec
void SpatialCalculator::Setting::initialize() {
    flags = 0xd;
    actor_matrix = nullptr;
    velocity = nullptr;
    attenuator = nullptr;
    listener_mask = 0xffff;
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

// NON_MATCHING: the original reloads mCone for the setAngle call (here it stays in a register).
// 0x7100b8f81c
void SpatialCalculator::setup(const Setting& setting) {
    reset();
    std::memcpy(&mSetting, &setting, sizeof(Setting));

    // A unified sound source has no size.
    if (mSetting.sound_source_size > 0.0f && mSetting.flags & 2)
        mSetting.sound_source_size = 0.0f;

    if (!mSetting.attenuator) {
        if (AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr())
            mSetting.attenuator = mgr->getDefaultAttenuator();
    }

    if (mSetting.attenuator) {
        if (AttenuationDirectivity* directivity = mSetting.attenuator->getAttenuationDirectivity()) {
            mCone = ConeFactory::instance()->create();
            if (mCone)
                mCone->setAngle(directivity->getInnerConeAngleRad(), directivity->getOuterConeAngleRad());
        }
    }

    if (mSetting.shape)
        mSetting.shape->attachSpatialCalculator_(this);
}

// 0x7100b8f708
void SpatialCalculator::initialize(s32 index, u32* dirty_counter, sead::Heap* heap) {
    if (mInitialized)
        return;

    s32 listener_num = SystemAccessor::getListenerMgr()->getListenerNum();
    if (listener_num > 0) {
        Result* results = new (heap, 8, std::nothrow) Result[listener_num];
        if (results) {
            mResultNum = listener_num;
            mResults = results;
        }
    }

    mDirtyCounter = dirty_counter;
    mReferredCount = 0;
    mPoolIndex = index;
    reset();
    mInitialized = true;
}

// NON_MATCHING: same logic; the original keeps the object pointer and the lock address in swapped registers, converts
// the cached result to a bool where it is read (here the conversion is moved to the return) and counts the audible
// listeners with a select instead of an or.
// 0x7100b8fb18
bool SpatialCalculator::calc(bool force) {
    bool result;
    if (mLastDirtyCounter == *mDirtyCounter) {
        result = mLastResult != 0;
    } else {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        result = mLastResult != 0;

        if (mSetting.actor_matrix) {
            if (mSetting.shape)
                mSetting.shape->setActorMatrixFromSpatialCalculator_(*mSetting.actor_matrix);

            if (mSetting.flags & 2) {
                // A unified sound source is never virtualized here.
                result = true;
            } else {
                s32 audible = 0;
                u64 index = 0;
                for (const Listener& listener : SystemAccessor::getListenerMgr()->mListeners) {
                    if (index < static_cast<u32>(mResultNum)) {
                        if (Result* r = &mResults[index]) {
                            if (mSetting.listener_mask & (1 << index)) {
                                r->is_valid = true;
                                if (calcByListener_(r, listener, index, force, &mDebuggerResult))
                                    audible = 1;
                            } else {
                                r->is_valid = false;
                            }
                        }
                    }
                    ++index;
                }
                result = !audible;
            }
            mLastDirtyCounter = *mDirtyCounter;
            mLastResult = result;
        }
    }
    return result;
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
