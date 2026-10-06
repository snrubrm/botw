#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>

namespace aal {

class Emitter;
class SoundSource;
class SpatialCalculator;
class SpatialPlayingParam;

/// The pools that the spatial calculators and the spatial playing parameters of the sound sources are allocated
/// from. TODO: incomplete; only the release of an element is declared.
class SpatialCalculatorPool {
public:
    /// 0x7100b90dec
    void free(SpatialCalculator* calculator);
};

class SpatialPlayingParamPool {
public:
    /// 0x7100b916fc
    void free(SpatialPlayingParam* param);
};

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
    /// Stops all the sound sources immediately.
    void stopAllSound();
    void execOnDestroyWaveAsset(u64 a, u64 b, bool c, bool d);
    void appendToActiveEmitterList(Emitter* emitter);
    void removeFromActiveEmitterList(Emitter* emitter);

    SpatialCalculatorPool* getSpatialCalculatorPool() const { return mSpatialCalculatorPool; }
    SpatialPlayingParamPool* getSpatialPlayingParamPool() const { return mSpatialPlayingParamPool; }

private:
    u8 _0[0x10];
    sead::OffsetList<Emitter> mActiveEmitters;
    u8 _28[0x50 - 0x28];
    sead::OffsetList<SoundSource> mSoundSources;
    SpatialCalculatorPool* mSpatialCalculatorPool;
    SpatialPlayingParamPool* mSpatialPlayingParamPool;
    sead::CriticalSection mEmitterCS;
    sead::CriticalSection mSoundSourceCS;
    /// Taken around the calls into the sound sources.
    sead::CriticalSection mSoundSourceCallCS;
};

}  // namespace aal
