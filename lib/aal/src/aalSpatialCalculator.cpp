#include "aal/aalSpatialCalculator.h"
#include <cmath>
#include <cstring>
#include <new>
#include <prim/seadScopedLock.h>
#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuationMgr.h"
#include "aal/aalAttenuator.h"
#include "aal/aalCone.h"
#include "aal/aalListener.h"
#include "aal/aalListenerMgr.h"
#include "aal/aalSettings.h"
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
                    if (static_cast<u32>(mResultNum) > index) {
                        if (Result* r = &mResults[index]) {
                            if (static_cast<u16>(mSetting.listener_mask & (1 << index))) {
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

// NON_MATCHING: same calls; the original sets up the matrix argument (result->_2c) before the destination
// of calcLocalMatrixForAngle in the case without the separate angle position.
// 0x7100b8fc8c
bool SpatialCalculator::calcByListener_(Result* result, const Listener& listener, s32 index, bool force,
                                        DebuggerResult* debugger_result) {
    if (!result)
        return false;

    if (mSetting.actor_matrix)
        result->_2c = *mSetting.actor_matrix;

    if (mSetting.shape) {
        sead::Vector3f position;
        mSetting.shape->calcPositionByListener(listener, &position);
        result->_2c.m[0][3] = position.x;
        result->_2c.m[1][3] = position.y;
        result->_2c.m[2][3] = position.z;
    }

    if (mSetting.flags & 2) {
        // A unified sound source is calculated by the unifier.
        if (debugger_result)
            debugger_result->code = 0x10003;
        return true;
    }

    calcListenerDistanceAndDirectivity_(result, listener);

    if (!calcDistReduction_(result, listener, index, debugger_result))
        return false;

    if (mSetting.shape && mSetting.shape->mFlags.isOnBit(Shape::SeparateAnglePosition)) {
        // The angle is calculated with another position than the distance.
        sead::Vector3f position;
        mSetting.shape->calcPositionForAngle(listener, &position);
        sead::Matrix34f matrix;
        if (mSetting.actor_matrix)
            matrix = *mSetting.actor_matrix;
        matrix.m[0][3] = position.x;
        matrix.m[1][3] = position.y;
        matrix.m[2][3] = position.z;
        listener.calcLocalMatrixForAngle(&result->_5c, matrix);
    } else {
        listener.calcLocalMatrixForAngle(&result->_5c, result->_2c);
    }

    calcAngle_(result, listener, force);
    calcDoppler_(result, listener);
    return true;
}

// NON_MATCHING: same calculation; the registers of the position are numbered differently.
// 0x7100b8fe80
void SpatialCalculator::calcListenerDistanceAndDirectivity_(Result* result, const Listener& listener) {
    sead::Vector3f position;
    result->_2c.getTranslation(position);

    if (mSetting.sound_source_size > 0.0f && mSetting.flags & 4) {
        // The sound source is a sphere: the nearest point of the sphere (towards the listener) is the position.
        sead::Vector3f listener_position;
        listener.mMatrix.getTranslation(listener_position);
        sead::Vector3f diff = listener_position - position;
        f32 distance = std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
        if (distance <= mSetting.sound_source_size)
            position = listener_position;
        else
            position += diff * (mSetting.sound_source_size / distance);
    }

    result->_8c = listener.calcLocalDistance(position);

    f32 distance_rate = 1.0f;
    if (mSetting.attenuator) {
        if (mSetting.flags & 0x20 || mSetting.attenuator->isListenerDirectivityEnabled())
            distance_rate = listener.mDirectivity.calcDistRate(position);
    }
    result->_90 = distance_rate;
}

// NON_MATCHING: in the original the case without the angle calculation stores its own zero angle (merged with the
// second distance) instead of jumping to the stores at the end.
// 0x7100b9033c
void SpatialCalculator::calcAngle_(Result* result, const Listener& listener, bool unified) {
    if (!result)
        return;

    if (mSetting.sound_source_size > 0.0f) {
        calcAngleWithSoundSourceSize_(result, listener, unified);
        return;
    }

    s32 angle_idx;
    if (mSetting.flags & 1) {
        f32 x = result->_5c.m[0][3];
        f32 z = result->_5c.m[2][3];
        f32 distance = std::sqrt(x * x + z * z);
        result->dist_2d[0] = distance;
        if (listener.mIs2D) {
            distance *= listener._ec;
            result->dist_2d[0] = distance;
        }
        if (distance == 0.0f)
            angle_idx = 0;
        else
            angle_idx = sead::MathCalcCommon<f32>::atan2Idx(-x, z) ^ 0x80000000;
    } else {
        result->dist_2d[0] = -1.0f;
        angle_idx = 0;
    }
    result->dist_2d[1] = result->dist_2d[0];
    result->angle_idx[0] = angle_idx;
    result->angle_idx[1] = angle_idx;
}

// NON_MATCHING: the original clamps the speed of the sound source before it asks the settings for the pitch limits
// (here the clamp moves into the branch that uses it) and orders the loads and multiplications a bit differently.
// 0x7100b9071c
void SpatialCalculator::calcDoppler_(Result* result, const Listener& listener) {
    if (!result)
        return;

    if (mSetting.doppler_factor <= 0.0f || result->_8c == 0.0f) {
        result->_c = 1.0f;
        return;
    }

    if (!mSetting.velocity)
        return;
    Settings* settings = SystemAccessor::getSettings();
    if (!settings)
        return;
    if (settings->mDopplerMode == 2)
        return;
    if (settings->mDopplerMode == 1) {
        result->_c = 1.0f;
        return;
    }

    // The speed of the listener and of the sound source along the line between them.
    f32 listener_speed = (listener._19c.x * -result->_5c.m[0][3] - listener._19c.y * result->_5c.m[1][3] -
                          listener._19c.z * result->_5c.m[2][3]) /
                         result->_8c;
    f32 source_speed = (mSetting.velocity->x * -result->_5c.m[0][3] - mSetting.velocity->y * result->_5c.m[1][3] -
                        mSetting.velocity->z * result->_5c.m[2][3]) /
                       result->_8c;

    f32 pitch;
    if (listener_speed == 0.0f && source_speed == 0.0f) {
        pitch = 1.0f;
    } else {
        f32 sound_speed = settings->mSoundDistancePerFrame;
        f32 limit = sound_speed / mSetting.doppler_factor;
        f32 source = source_speed < limit ? source_speed : limit;
        f32 listener_v = listener_speed < limit ? listener_speed : limit;
        f32 listener_term = mSetting.doppler_factor * listener_v;
        f32 pitch_min = settings->getDopplerPitchMin();
        f32 pitch_max = settings->getDopplerPitchMax();
        pitch = pitch_min;
        if (listener_term < sound_speed) {
            f32 source_term = mSetting.doppler_factor * source;
            if (source_term >= sound_speed) {
                pitch = pitch_max;
            } else {
                f32 rate = (sound_speed - listener_term) / (sound_speed - source_term);
                if (rate >= pitch_min) {
                    if (rate > pitch_max)
                        pitch = pitch_max;
                    else
                        pitch = rate;
                }
            }
        }
    }
    result->_c = pitch;
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
