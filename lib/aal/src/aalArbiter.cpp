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
    for (SoundSource& sound_source : mSoundSources)
        sound_source.detachSoundGroup();
}

// 0x7100b9eacc
void Arbiter::dumpActiveSoundSource() const {}

// 0x7100b9ead0
void Arbiter::setEmitterAllocateCallback(IEmitterAllocateCallback* callback) {}

// 0x7100b9ead4
void Arbiter::appendToActiveEmitterList(Emitter* emitter) {
    if (emitter) {
        sead::ScopedLock<sead::CriticalSection> lock(&mEmitterCS);
        mActiveEmitters.pushBack(emitter);
    }
}

// 0x7100b9eb4c
void Arbiter::removeFromActiveEmitterList(Emitter* emitter) {
    if (emitter) {
        sead::ScopedLock<sead::CriticalSection> lock(&mEmitterCS);
        mActiveEmitters.erase(emitter);
    }
}

}  // namespace aal
