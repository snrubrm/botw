#include "aal/aalHandle.h"
#include "aal/aalSoundSource.h"

namespace aal {

const Handle Handle::cInvalid;

// 0x7100b75d44
Handle::Handle() = default;

// 0x7100b76248
SoundSource* Handle::getSoundSource() {
    if (!mSoundSource)
        return nullptr;
    return mId == mSoundSource->mId ? mSoundSource : nullptr;
}

// 0x7100b7626c
const SoundSource* Handle::getSoundSource() const {
    if (!mSoundSource)
        return nullptr;
    return mId == mSoundSource->mId ? mSoundSource : nullptr;
}

// 0x7100b762b8
void Handle::attachSoundSource(SoundSource* source) {
    mSoundSource = source;
    if (source)
        mId = source->mId;
}

// 0x7100b75d50
bool Handle::isEnabled() const {
    return mSoundSource && mId == mSoundSource->mId;
}

// 0x7100b75d74
bool Handle::isActive() const {
    if (auto* source = getSoundSource())
        return source->mState != 0 && source->mState != 7;
    return false;
}

// 0x7100b75dbc
void Handle::stop(f32 fade_time, f32 release_time) {
    if (auto* source = getSoundSource())
        source->stop(fade_time, release_time);
}

// 0x7100b75de0
void Handle::pause(bool pause, f32 fade_time) {
    if (auto* source = getSoundSource())
        source->pause(pause, fade_time);
}

// 0x7100b75e08
void Handle::pause(sead::BitFlag8 mask, bool pause, f32 fade_time) {
    if (auto* source = getSoundSource())
        source->pause(mask, pause, fade_time);
}

// 0x7100b75e34
void Handle::setVolume(f32 volume) {
    if (auto* source = getSoundSource())
        source->mParam.setVolume(volume);
}

// 0x7100b75e58
void Handle::setTrackVolume(sead::BitFlag32 tracks, f32 volume) {
    if (auto* source = getSoundSource())
        source->setTrackVolume(tracks, volume);
}

// 0x7100b75e80
void Handle::setPitch(f32 pitch) {
    if (auto* source = getSoundSource())
        source->mParam.setPitch(pitch);
}

// 0x7100b75ea4
void Handle::setSpread(f32 spread) {
    if (auto* source = getSoundSource())
        source->mParam.setSpread(spread);
}

// 0x7100b75ec8
void Handle::setLfe(f32 lfe) {
    if (auto* source = getSoundSource())
        source->mParam.setLfe(lfe);
}

// 0x7100b75eec
void Handle::setLpf(f32 lpf) {
    if (auto* source = getSoundSource())
        source->mParam.setLpf(lpf);
}

// 0x7100b75f10
void Handle::setBiquadFilter(int index, f32 value) {
    if (auto* source = getSoundSource())
        source->mParam.setBiquadFilter(index, value);
}

// 0x7100b75f34
void Handle::setBiquadType(int type) {
    if (auto* source = getSoundSource())
        source->mParam.setBiquadType(type);
}

// 0x7100b75f58
void Handle::setBiquadValue(f32 value) {
    if (auto* source = getSoundSource())
        source->mParam.setBiquadValue(value);
}

// 0x7100b75f7c
void Handle::setFadeCurveType(FadeCurveType type) {
    if (auto* source = getSoundSource())
        source->mFadeCurveType = type;
}

// 0x7100b75f9c
bool Handle::setStartDelayTime(f32 delay_time) {
    if (auto* source = getSoundSource())
        return source->setStartDelayTime(delay_time);
    return false;
}

// 0x7100b75fc4
bool Handle::setFadeInTime(f32 fade_in_time) {
    if (auto* source = getSoundSource())
        return source->setFadeInTime(fade_in_time);
    return false;
}

// 0x7100b75fec
bool Handle::setReleaseCurveType(FadeCurveType type) {
    if (auto* source = getSoundSource())
        return source->setReleaseCurveType(type);
    return false;
}

// 0x7100b76044
bool Handle::isPaused() const {
    if (auto* source = getSoundSource())
        return source->mPauseFlags != 0;
    return false;
}

// 0x7100b7607c
bool Handle::isPaused(sead::BitFlag8 mask) const {
    if (auto* source = getSoundSource())
        return (source->mPauseFlags & mask) != 0;
    return false;
}

// 0x7100b760b8
bool Handle::isVirtualized() const {
    if (auto* source = getSoundSource())
        return source->isVirtualized();
    return false;
}

// 0x7100b760e0
u32 Handle::getPlaySamplePosition() const {
    if (auto* source = getSoundSource())
        return source->getPlaySamplePosition();
    return 0;
}

// 0x7100b76108
f32 Handle::getPlayingTime() const {
    if (auto* source = getSoundSource())
        return source->mPlayingTime;
    return 0.0f;
}

// 0x7100b7612c
const AssetInfo* Handle::getAssetInfo() const {
    if (auto* source = getSoundSource())
        return source->getAssetInfo();
    return nullptr;
}

// 0x7100b76154
const char* Handle::getAssetName() const {
    if (auto* source = getSoundSource())
        return source->getAssetName();
    return nullptr;
}

// 0x7100b7617c
SoundGroup* Handle::getSoundGroup() const {
    if (auto* source = getSoundSource())
        return source->mSoundGroup;
    return nullptr;
}

// 0x7100b761f4
MarkerController* Handle::getMarkerController() const {
    if (auto* source = getSoundSource())
        return source->mMarkerController;
    return nullptr;
}

// 0x7100b76224
f32 Handle::getDelayTime() const {
    if (auto* source = getSoundSource())
        return source->mStartDelayTime;
    return 0.0f;
}

// 0x7100b76290
SoundParam* Handle::getDefaultParamPtr() {
    if (!mSoundSource)
        return nullptr;
    return mId == mSoundSource->mId ? &mSoundSource->mDefaultParam : nullptr;
}

}  // namespace aal
