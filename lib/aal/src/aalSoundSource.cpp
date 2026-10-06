#include "aal/aalSoundSource.h"
#include <math/seadMathCalcCommon.h>
#include "aal/aalEmitter.h"
#include "aal/aalGroup.h"
#include "aal/aalSoundSourceUnifier.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b77d6c
void SoundSource::pause(bool pause, f32 fade_time) {
    this->pause(sead::BitFlag8(0xff), pause, fade_time);
}

// 0x7100b77e8c
bool SoundSource::setStartDelayTime(f32 delay_time) {
    const s32 state = mState;
    bool result = false;
    if (delay_time >= 0.0f && state <= 2) {
        mStartDelayTime = delay_time;
        mState = delay_time > 0.0f ? 1 : 2;
        result = true;
    }
    return result;
}

// 0x7100b77ec4
bool SoundSource::setFadeInTime(f32 fade_in_time) {
    const s32 state = mState;
    bool result = false;
    if (fade_in_time >= 0.0f && state <= 2) {
        mFadeInTime = fade_in_time;
        result = true;
    }
    return result;
}

// 0x7100b77e5c
void SoundSource::startPrepared() {
    mPlayingStateController->mSoundController->startPrepared();
    mState = 4;
}

// 0x7100b781a4
void SoundSource::setPriority(f32 priority) {
    if (priority >= 0.0f && priority <= 1.0f)
        mPriority = priority;
}

// 0x7100b783b8
f32 SoundSource::getFadeInTimeIfBeforePlaying() const {
    if (mState <= 2)
        return mFadeInTime;
    return -1.0f;
}

// 0x7100b78094
bool SoundSource::setStreamRegionCallback(SoundController::StreamRegionCallback callback,
                                          void* user_data) {
    if (mState <= 2) {
        mPlayingStateController->mSoundController->setStreamRegionCallback(callback, user_data);
        return true;
    }
    return false;
}

// 0x7100b780c8
void SoundSource::setIgnorePrefetch(bool ignore) {
    if (mState <= 2)
        mPlayingStateController->mSoundController->setIgnorePrefetch(ignore);
}

// 0x7100b78048
bool SoundSource::setStartSamplePos(s32 position) {
    const s32 state = mState;
    bool result = false;
    if (position >= 0 && state <= 2) {
        mStartSamplePos = position;
        mPlayingStateController->mSoundController->setStartSampleOffset(position);
        result = true;
    }
    return result;
}

// 0x7100b78084
const AssetInfo* SoundSource::getAssetInfo() const {
    return mPlayingStateController->mSoundController->mAssetInfo;
}

// 0x7100b78310
bool SoundSource::isLooped() const {
    if (auto* info = mPlayingStateController->mSoundController->mAssetInfo)
        return info->mFlags & 1;
    return false;
}

// 0x7100b78178
f32 SoundSource::getTrackVolume(s32 track) const {
    if (static_cast<u32>(track) <= 7)
        return mTrackVolume[track] * (1.0f / 255.0f);
    return 0.0f;
}

// 0x7100b77eec
bool SoundSource::setReleaseCurveType(FadeCurveType type) {
    if (mState <= 2) {
        mPlayingStateController->mSoundController->setFadeCurveType(type);
        return true;
    }
    return false;
}

// 0x7100b781c0
bool SoundSource::isVirtualized() const {
    return mVirtualizedBy != 0;
}

// 0x7100b77ca0
void SoundSource::kill() {
    reset();
}

inline void SoundSource::freeUnifierSource_() {
    if (mUnifierSource) {
        if (auto* unifier = SystemAccessor::getSoundSourceUnifier())
            unifier->freeSource(mUnifierSource, -1.0f);
        mUnifierSource = nullptr;
    }
}

/// Stops the sound immediately and finishes the source.
inline void SoundSource::finishNow_() {
    mPriority = 0.0f;
    mPlayingStateController->stopForce();
    if (mEmitter) {
        if (_1e8 || _1e0)
            mEmitter->removeSoundSource(this);
        mEmitter = nullptr;
    }
    mState = 7;
}

// 0x7100b777dc
void SoundSource::stopForce() {
    freeUnifierSource_();
    finishNow_();
}

// 0x7100b772cc
void SoundSource::execOnDestroyWaveAsset(u64 a, u64 b, bool c, bool d) {
    if (mPlayingStateController->execOnDestroyWaveAsset(a, b, c, d))
        finishNow_();
}

// 0x7100b7900c
void SoundSource::execOnFianlizeSoundSourceUnifierSource() {
    if (mUnifierSource)
        finishNow_();
    mUnifierSource = nullptr;
}

// 0x7100b77f94
bool SoundSource::setReleaseTime(f32 release_time) {
    if (mState <= 2) {
        if (release_time < 0.0f && mSoundGroup)
            release_time = mSoundGroup->getReleaseTime();
        mPlayingStateController->setReleaseTime(sead::Mathf::clampMin(release_time, 0.0f));
        return true;
    }
    return false;
}

// 0x7100b778b8
void SoundSource::detachSoundGroup() {
    if (mSoundGroup) {
        mSoundGroup->removeSound(this);
        mSoundGroup = nullptr;
    }
}

// 0x7100b78134
bool SoundSource::prepare(bool prepare) {
    if (mState <= 2) {
        mPrepareFlags = !prepare ? mPrepareFlags & ~4 : mPrepareFlags | 4;
        return true;
    }
    return false;
}

// 0x7100b7816c
void SoundSource::setInteriorNum(s32 interior_num) {
    (void)mState;
    mInteriorNum = interior_num;
}

// 0x7100b77334
s32 SoundSource::getChannelNum(s32 track) const {
    if (track >= 0 && track < mTrackNum)
        return mChannelNum[track];
    return 0;
}

// 0x7100b780e8
bool SoundSource::setSpeakerBalanceSupplier(ISpeakerBalanceSupplier* supplier) {
    if (mState <= 2 && !mSpeakerBalanceSupplier) {
        mSpeakerBalanceSupplier = supplier;
        if (supplier)
            aggregateAndClampParams_();
        return true;
    }
    return false;
}

// 0x7100b7850c
bool SoundSource::isAttachedSound() const {
    return mPlayingStateController->mSoundController->mState != 0;
}

// 0x7100b78334
bool SoundSource::canVirtualize() const {
    return static_cast<s32>(mPlayingStateController->mVirtualizeMode) != 0 && !mSpatialSetting.isUnified();
}

// 0x7100b783d4
const SpatialCalculator::Result* SoundSource::getSpatialCalcResult(s32 index) const {
    if (!mSpatialSetting.isUnified() && mSpatialCalculator && mSpatialCalculator->getResultNum() > index)
        return mSpatialCalculator->getResult(index);
    return nullptr;
}

// 0x7100b782f4
const sead::SafeString& SoundSource::getSoundGroupName() const {
    return mSoundGroup ? mSoundGroup->getObjName() : sead::SafeString::cEmptyString;
}

// 0x7100b78a60
f32 SoundSource::getCurrentFadeInOutVolume() const {
    return SimpleTimedFader::toCurvedValue(mFadeCurveType, mFader->getValue());
}

// 0x7100b77850
void SoundSource::setTrackVolume(sead::BitFlag32 tracks, f32 volume) {
    if (volume >= 0.0f && volume <= 1.0f) {
        const u8 value = volume * 255.0f;
        for (s32 i = 0; i < 8; ++i) {
            if (tracks.isOnBit(i))
                mTrackVolume[i] = value;
        }
    }
}

inline void SoundSource::pauseImpl_(bool pause, f32 fade_time) {
    if (mSpatialSetting.isUnified()) {
        if (mUnifierSource)
            mUnifierSource->pause(pause, fade_time);
    } else {
        mPlayingStateController->pause(pause, fade_time);
    }
}

// 0x7100b77d78
void SoundSource::pause(sead::BitFlag8 mask, bool pause, f32 fade_time) {
    const u8 prev = mPauseFlags.getDirect();
    mPauseFlags.setDirect(pause ? prev | mask.getDirect() : prev & ~mask.getDirect());
    const u8 now = mPauseFlags.getDirect();
    if (prev == 0) {
        if (now != 0)
            pauseImpl_(true, fade_time);
    } else if (now == 0) {
        pauseImpl_(false, fade_time);
    }
}

}  // namespace aal
