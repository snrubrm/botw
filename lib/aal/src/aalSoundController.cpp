#include "aal/aalSoundController.h"
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9fd14
void PlayingStateController::setReleaseTime(f32 release_time) {
    if (release_time >= 0.0f)
        mReleaseTime = release_time;
}

// 0x7100ba025c
s32 PlayingStateController::getPlayingSamplePos() const {
    if (mState != 0) {
        if (mState == 3)
            return static_cast<s32>(mSamplePos);
        if (mSoundController)
            return mSoundController->getPlayingSamplePos();
    }
    return -1;
}

// 0x7100ba2098
void SoundController::setPitch(f32 pitch) {
    if (mSoundHandle && mSoundHandle->m_pSound)
        mSoundHandle->m_pSound->SetPitch(pitch);
}

// 0x7100ba21e8
void SoundController::setLpf(f32 lpf) {
    if (mSoundHandle && mSoundHandle->m_pSound)
        mSoundHandle->m_pSound->SetLpfFreq(-lpf);
}

// 0x7100ba255c
bool SoundController::isInnerPaused() const {
    if (mSoundHandle && mSoundHandle->m_pSound && mSoundHandle->m_pSound->IsPause())
        return true;
    return false;
}

// 0x7100ba1d64
void SoundController::startPrepared() {
    if (mSoundHandle && mSoundHandle->m_pSound)
        mSoundHandle->m_pSound->StartPrepared();
}

// 0x7100ba2058
void SoundController::setFadeCurveType(FadeCurveType type) {
    mFadeCurveType = type;
}

// 0x7100ba2060
void SoundController::setStartSampleOffset(u32 offset) {
    mStartSampleOffset = offset;
}

// 0x7100ba2068
void SoundController::setStreamRegionCallback(StreamRegionCallback callback, void* user_data) {
    mStreamRegionCallback = callback;
    mStreamRegionUserData = user_data;
}

// 0x7100ba2070
void SoundController::setIgnorePrefetch(bool ignore) {
    if (mAssetInfo)
        mAssetInfo->mFlags = ignore ? mAssetInfo->mFlags | 4 : mAssetInfo->mFlags & ~4;
}

// 0x7100ba228c
bool SoundController::checkDeviceEnabledOnOutputLine(DeviceType device, u32 output_line) {
    return output_line & 1;
}

// 0x7100b9fd24
void PlayingStateController::setVirtualizeMode(VirtualizeMode mode) {
    mVirtualizeMode = mode;
}

// 0x7100ba1344
SoundController::SoundController() = default;

// 0x7100ba1370 / 0x7100ba1440
SoundController::~SoundController() {
    finalize();
}

// 0x7100ba13e0
void SoundController::finalize() {
    if (mAssetInfo) {
        delete mAssetInfo;
        mAssetInfo = nullptr;
    }
    if (mFader) {
        delete mFader;
        mFader = nullptr;
    }
    if (auto* handle = mSoundHandle) {
        handle->DetachSound();
        delete handle;
        mSoundHandle = nullptr;
    }
}

// 0x7100ba1d1c
void SoundController::release(f32 fade_time) {
    if (mSoundHandle && mFader && mSoundHandle->m_pSound) {
        mFader->moveTo(0.0f, fade_time);
        mState = 3;
    }
}

// 0x7100ba1e88
void SoundController::pause(bool pause, f32 fade_time) {
    if (mSoundHandle) {
        if (auto* settings = SystemAccessor::getSettings()) {
            const s32 fade_frames = static_cast<s32>(fade_time / settings->mCalcTimeStep);
            if (pause) {
                if (mState == 1) {
                    if (mSoundHandle->m_pSound)
                        mSoundHandle->m_pSound->Pause(true, fade_frames);
                    mState = 2;
                }
            } else if (mState == 2) {
                if (mSoundHandle->m_pSound)
                    mSoundHandle->m_pSound->Pause(false, fade_frames);
                mState = 1;
            }
        }
    }
}

// 0x7100b9fb60
PlayingStateController::PlayingStateController() = default;

// 0x7100b9fb8c / 0x7100b9fc20
PlayingStateController::~PlayingStateController() {
    finalize();
}

// 0x7100b9fbe0
void PlayingStateController::finalize() {
    if (mSoundController) {
        mSoundController->finalize();
        delete mSoundController;
        mSoundController = nullptr;
    }
}

// 0x7100b9fc7c
void PlayingStateController::initialize(sead::Heap* heap) {
    mSoundController = new (heap, 8) SoundController;
    if (mSoundController)
        mSoundController->initialize(heap);
}

// 0x7100b9fcd8
void PlayingStateController::reset() {
    if (mSoundController)
        mSoundController->reset();
    mState = 0;
    mVirtualizeMode = static_cast<VirtualizeMode>(1);
    mPaused = false;
    mReleaseTime = 0.0f;
    _20 = 0.0f;
    mSamplePos = 0.0f;
}

// 0x7100b9fd2c
bool PlayingStateController::start(bool prepare) {
    if (mSoundController) {
        mSoundController->release(0.0f);
        if (mSoundController->start(0.0f, prepare)) {
            mState = 1;
            return true;
        }
    }
    return false;
}

// 0x7100b9fd8c
void PlayingStateController::stopWithRelease() {
    const f32 release_time = mReleaseTime;
    mCS.lock();
    if (mSoundController) {
        mSoundController->release(release_time);
        mState = release_time != 0.0f ? 2 : 0;
    } else {
        mState = 0;
    }
    mSamplePos = 0.0f;
    mPaused = false;
    mCS.unlock();
}

// 0x7100b9fdf4
void PlayingStateController::stopForce() {
    mCS.lock();
    if (mSoundController)
        mSoundController->release(0.0f);
    mState = 0;
    mSamplePos = 0.0f;
    mPaused = false;
    mCS.unlock();
}

// 0x7100b9fe3c
void PlayingStateController::preCalc() {
    if (mState == 4)
        restart_(static_cast<u32>(mSamplePos), _20);
}

// 0x7100b9ff50
void PlayingStateController::calc() {
    if (mSoundController) {
        mSoundController->calc();
        if (mState >= 1 && mState <= 2 && mSoundController->mState == 0) {
            mState = 0;
            updateVirtualPlayingPos_();
        }
    }
}

// 0x7100ba01d8
void PlayingStateController::unvirtualize() {
    mCS.lock();
    if (mState == 3 && static_cast<s32>(mVirtualizeMode) == 2) {
        mSamplePos = 0.0f;
        mState = 4;
    }
    mCS.unlock();
}

// 0x7100ba0228
void PlayingStateController::pause(bool pause, f32 fade_time) {
    if (mSoundController) {
        mSoundController->pause(pause, fade_time);
        mPaused = pause;
    }
}

}  // namespace aal
