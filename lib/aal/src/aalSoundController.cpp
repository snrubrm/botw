#include "aal/aalSoundController.h"
#include <basis/seadNew.h>
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

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

// 0x7100ba1344
SoundController::SoundController() = default;

// 0x7100ba1370 / 0x7100ba1440
SoundController::~SoundController() {
    finalize();
}

// 0x7100ba14b0
void SoundController::initialize(sead::Heap* heap) {
    if (!mAssetInfo)
        mAssetInfo = new (heap, 8) AssetInfo;
    if (!mFader)
        mFader = new (heap, 8) SimpleTimedFader(1.0f);
    if (!mSoundHandle)
        mSoundHandle = new (heap, 8) nn::atk::SoundHandle;
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

// 0x7100ba1f20
void SoundController::reset() {
    release(0.0f);
    if (mAssetInfo)
        *mAssetInfo = AssetInfo();
    mFadeCurveType = static_cast<FadeCurveType>(0);
    mStartSampleOffset = 0;
    mStreamRegionCallback = nullptr;
    mStreamRegionUserData = nullptr;
    mChannelPriority = 127;
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

}  // namespace aal
