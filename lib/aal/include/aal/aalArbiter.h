#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>

namespace aal {

class Emitter;
class SoundSource;

/// Allocates and keeps track of the emitters and the sound sources.
/// TODO: incomplete (the constructor, the pools at +0x68 / +0x70 and most functions are not modeled).
class Arbiter {
public:
    class IEmitterAllocateCallback;

    /// The memory needed for the given number of emitters.
    static u32 getRequireEmitterCreateHeap(s32 emitter_num);

    void setEmitterAllocateCallback(IEmitterAllocateCallback* callback);
    void dumpActiveSoundSource() const;
    /// Unregisters the sound source (its id is reset).
    void freeSoundSource(SoundSource* sound_source);
    void detachGroupFromSoundSourceAll();
    void appendToActiveEmitterList(Emitter* emitter);
    void removeFromActiveEmitterList(Emitter* emitter);

private:
    u8 _0[0x10];
    sead::OffsetList<Emitter> mActiveEmitters;
    u8 _28[0x50 - 0x28];
    sead::OffsetList<SoundSource> mSoundSources;
    u8 _68[0x78 - 0x68];
    sead::CriticalSection mEmitterCS;
    sead::CriticalSection mSoundSourceCS;
};

}  // namespace aal
