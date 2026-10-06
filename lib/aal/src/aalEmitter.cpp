#include "aal/aalEmitter.h"
#include <prim/seadScopedLock.h>
#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b9ec7c
u32 Emitter::getRequiredMemSize() {
    return LimiterUtil::getMaxActiveSoundLimiterSize() + 0x1e0;
}

// 0x7100b9efa4
void Emitter::calc() {
    if (mLimiter) {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mLimiter->calcLimit(mSoundSources);
    }
}

// 0x7100b9f208
bool Emitter::isActive() const {
    if (mSoundSources) {
        for (SoundSource& sound_source : *mSoundSources) {
            if (sound_source.mState != 0 && sound_source.mState != 7)
                return true;
        }
    }
    return false;
}

// 0x7100b9f394
void Emitter::setDebugSolo(bool solo) {
    if (solo) {
        mDebugFlags |= 1;
        mDebugFlags &= ~2;
    } else {
        mDebugFlags &= ~1;
    }
}

// 0x7100b9f3c0
void Emitter::setDebugMute(bool mute) {
    const u8 flags = mDebugFlags;
    const u8 cleared = flags & ~2;
    const u8 set = flags | 2;
    mDebugFlags = (flags & 1) ? cleared : (!mute ? cleared : set);
}

// 0x7100b9f3e8
bool Emitter::isDebugMuted() const {
    return false;
}

}  // namespace aal
