#include "aal/aalSoundController.h"

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

}  // namespace aal
