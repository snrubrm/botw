#include "aal/aalSoundSourceUnifier.h"
#include "aal/aalSpeakerBalanceUnifier.h"
#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: the two stores of the trailing members come after the list initialization in the original.
// 0x7100b8efc8
SoundSourceUnifierTarget::SoundSourceUnifierTarget() : mUnifier(nullptr), _70(0), _78(nullptr) {
    mSources.initOffset(offsetof(SoundSourceUnifierSource, mTargetListNode));
}

// 0x7100b8f060
SoundSourceUnifierTarget::~SoundSourceUnifierTarget() {
    finalize();
}

// 0x7100b8f0b8
void SoundSourceUnifierTarget::finalize() {
    if (mUnifier) {
        SystemAccessor::getSpeakerBalanceUnifierMgr()->freeSpeakerBalanceUnifier(mUnifier);
        mUnifier = nullptr;
    }
    mSources.clear();
    mName.clear();
    _70 = 0;
    _78 = nullptr;
}

// 0x7100b8f38c
void SoundSourceUnifierTarget::stopSound(f32 fade_time) {
    mHandle.stop(fade_time, 0.0f);
}

// 0x7100b8f398
void SoundSourceUnifierTarget::addSource(SoundSourceUnifierSource* source) {
    if (source && mUnifier && source->mUnifiable) {
        mUnifier->addUnifiable(source->mUnifiable);
        mSources.pushBack(source);
    }
}

// 0x7100b8f3ec
void SoundSourceUnifierTarget::removeSource(SoundSourceUnifierSource* source) {
    if (source && mUnifier) {
        if (source->mUnifiable)
            mUnifier->removeUnifiable(source->mUnifiable);
        if (mSources.isNodeLinked(source))
            mSources.erase(source);
    }
}

// 0x7100b8f44c
bool SoundSourceUnifierTarget::isActive() const {
    return mHandle.isActive();
}

}  // namespace aal
