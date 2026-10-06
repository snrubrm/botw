#include "aal/aalSoundSource.h"

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

// 0x7100b781c0
bool SoundSource::isVirtualized() const {
    return mVirtualizedBy != 0;
}

}  // namespace aal
