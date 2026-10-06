#include "aal/aalArbiter.h"
#include <prim/seadScopedLock.h>
#include "aal/aalEmitter.h"
#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b9e5d0
void Arbiter::freeSoundSource(SoundSource* sound_source) {
    if (sound_source) {
        sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCS);
        sound_source->mId = 0;
        if (mSoundSources.isNodeLinked(sound_source))
            mSoundSources.erase(sound_source);
    }
}

// 0x7100b9e7cc
u32 Arbiter::getRequireEmitterCreateHeap(s32 emitter_num) {
    return Emitter::getRequiredMemSize() * emitter_num;
}

// 0x7100b9ea60
void Arbiter::detachGroupFromSoundSourceAll() {
    sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCS);
    for (SoundSource& sound_source : mSoundSources.robustRange())
        sound_source.detachSoundGroup();
}

// 0x7100b9e8f8
void Arbiter::stopAllSound() {
    sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCS);
    for (SoundSource& sound_source : mSoundSources.robustRange()) {
        sead::ScopedLock<sead::CriticalSection> call_lock(&mSoundSourceCallCS);
        sound_source.stop(-1.0f, 0.0f);
    }
}

// 0x7100b9e99c
void Arbiter::execOnDestroyWaveAsset(u64 a, u64 b, bool c, bool d) {
    sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCS);
    for (SoundSource& sound_source : mSoundSources.robustRange()) {
        sead::ScopedLock<sead::CriticalSection> call_lock(&mSoundSourceCallCS);
        sound_source.execOnDestroyWaveAsset(a, b, c, d);
    }
}

// 0x7100b9eacc
void Arbiter::dumpActiveSoundSource() const {}

// 0x7100b9ead0
void Arbiter::setEmitterAllocateCallback(IEmitterAllocateCallback* callback) {}

// 0x7100b9ead4
void Arbiter::appendToActiveEmitterList(Emitter* emitter) {
    if (emitter) {
        sead::ScopedLock<sead::CriticalSection> lock(&mEmitterCS);
        if (!mActiveEmitters.isNodeLinked(emitter))
            mActiveEmitters.pushBack(emitter);
    }
}

// 0x7100b9eb4c
void Arbiter::removeFromActiveEmitterList(Emitter* emitter) {
    if (emitter) {
        sead::ScopedLock<sead::CriticalSection> lock(&mEmitterCS);
        if (mActiveEmitters.isNodeLinked(emitter))
            mActiveEmitters.erase(emitter);
    }
}

}  // namespace aal
