#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalTimedFader.h"

namespace aal {

void SoundGroup::allowEmit(bool allow) {
    mEmitFlags.setDirect(allow ? 0xff : 0);
}

void SoundGroup::allowEmit(sead::BitFlag8 flags, bool allow) {
    if (allow)
        mEmitFlags.set(flags);
    else
        mEmitFlags.reset(flags);
}

void SoundGroup::silence(bool silence, f32 fade_time) {
    if (fade_time >= 0.0f && mSilenceFader) {
        if (silence)
            mSilenceFader->moveTo(0.0f, fade_time);
        else
            mSilenceFader->moveTo(1.0f, fade_time);
    }
}

void SoundGroup::setReleaseTime(f32 release_time) {
    if (release_time >= 0.0f)
        mReleaseTime = release_time;
}

bool SoundGroup::pushFrontChild_(Group* child) {
    return false;
}

bool SoundGroup::pushBackChild_(Group* child) {
    return false;
}

bool SoundGroup::insertBeforeChild_(Group* child, Group* before) {
    return false;
}

bool SoundGroup::insertAfterChild_(Group* child, Group* after) {
    return false;
}

void SoundGroup::removeChild_(Group* child) {}

bool SoundGroup::isSoundGroup() const {
    return true;
}

bool SoundGroup::isGroupFolder() const {
    return false;
}

void SoundGroup::addToPlayingSoundSources(SoundSource* sound_source) {
    if (sound_source)
        mPlayingSoundSources.pushBack(sound_source);
}

void SoundGroup::calcSilence_() {
    if (mSilenceFader) {
        mSilenceFader->calc();
        mAggregatedParam->setVolume(mAggregatedParam->getVolume() * mSilenceFader->getValue());
    }
}

void SoundGroup::calcActiveSoundLimit() {
    mLimiter->addToActiveSoundLimitList(&mPlayingSoundSources);
    mLimiter->calcActiveSoundLimit();
}

void SoundGroup::calcNumSounds() {
    for (SoundSource& sound_source : mPlayingSoundSources) {
        if (sound_source.mSpatialSetting.isUnified()) {
            ++_15c;
        } else if (sound_source.isVirtualized()) {
            ++_158;
        } else {
            ++mDuckingCount;
            for (s32 i = 0; i < sound_source.mTrackNum; ++i)
                _154 += sound_source.getChannelNum(i);
        }
    }
    Group::calcNumSounds();
}

}  // namespace aal
