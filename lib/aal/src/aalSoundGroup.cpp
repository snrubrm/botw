#include <basis/seadNew.h>
#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalTimedFader.h"

namespace aal {

namespace {
/// The offset of the list node of SoundSource that is used for the playing sounds of a group.
constexpr s32 cSoundSourceListNodeOffset = 0x1d0;
}  // namespace

// 0x7100b81f60
SoundGroup::SoundGroup() : mReleaseTime(0.0f), mEmitFlags(0xff), mSilenceFader(nullptr) {
    mPlayingSoundSources.initOffset(cSoundSourceListNodeOffset);
}

// 0x7100b81fd4 (D1) / 0x7100b820b4 (D0), and their thunks for the second base
SoundGroup::~SoundGroup() {
    finalize();
}

// 0x7100b821a4
void SoundGroup::initialize(const sead::SafeString& name, sead::Heap* heap) {
    if (mInitialized)
        return;
    mSilenceFader = new (heap) SimpleTimedFader(1.0f);
    if (mSilenceFader)
        mSilenceFader->moveTo(1.0f, 0.0f);
    Group::initialize(name, heap);
}

// 0x7100b82228
void SoundGroup::finalize() {
    if (!mInitialized)
        return;
    if (mSilenceFader) {
        delete mSilenceFader;
        mSilenceFader = nullptr;
    }
    Group::finalize();
}

// 0x7100b82590
void SoundGroup::allowEmit(bool allow) {
    mEmitFlags.setDirect(allow ? 0xff : 0);
}

// 0x7100b8259c
void SoundGroup::allowEmit(sead::BitFlag8 flags, bool allow) {
    if (allow)
        mEmitFlags.set(flags);
    else
        mEmitFlags.reset(flags);
}

// 0x7100b825c0
void SoundGroup::silence(bool silence, f32 fade_time) {
    if (fade_time >= 0.0f && mSilenceFader) {
        if (silence)
            mSilenceFader->moveTo(0.0f, fade_time);
        else
            mSilenceFader->moveTo(1.0f, fade_time);
    }
}

// 0x7100b825ec
void SoundGroup::setReleaseTime(f32 release_time) {
    if (release_time >= 0.0f)
        mReleaseTime = release_time;
}

// 0x7100b82848 .. 0x7100b82868: SoundGroup has no children
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

// 0x7100b82ae0 / 0x7100b82ae8
bool SoundGroup::isSoundGroup() const {
    return true;
}

bool SoundGroup::isGroupFolder() const {
    return false;
}

// 0x7100b825fc
bool SoundGroup::addSound(SoundSource* sound_source) {
    if (!sound_source)
        return false;
    if (!(sound_source->mSpatialSetting.isUnified() || sound_source->mState > 2 || sound_source->isLooped())) {
        if (!mLimiter->limitRequestInterval(sound_source))
            return false;
        bool added;
        {
            sead::ScopedLock<sead::CriticalSection> lock(&mCS);
            added = mLimiter->addToActiveSoundLimitList(sound_source);
        }
        if (added)
            return true;
    }
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mPlayingSoundSources.pushBack(sound_source);
    return true;
}

// 0x7100b826bc
void SoundGroup::addToPlayingSoundSources(SoundSource* sound_source) {
    if (sound_source)
        mPlayingSoundSources.pushBack(sound_source);
}

// 0x7100b8286c
void SoundGroup::calcSilence_() {
    if (mSilenceFader) {
        mSilenceFader->calc();
        mAggregatedParam->setVolume(mAggregatedParam->getVolume() * mSilenceFader->getValue());
    }
}

// 0x7100b828b4
void SoundGroup::calcActiveSoundLimit() {
    mLimiter->addToActiveSoundLimitList(&mPlayingSoundSources);
    mLimiter->calcActiveSoundLimit();
}

// 0x7100b828e0
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
