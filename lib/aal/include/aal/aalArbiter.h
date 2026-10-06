#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalSpatialCalculatorPool.h"

namespace aal {

class Emitter;
class ISpatialCalculatorFactory;
class SoundSource;
class SpatialPlayingParam;
class SpatialPlayingParamPool;

/// Allocates and keeps track of the emitters and the sound sources.
/// TODO: incomplete (calc, finalize and the unknown members are not decompiled).
class Arbiter : public sead::hostio::Node {
public:
    /// Is told about the emitters that are created and destroyed.
    class IEmitterAllocateCallback {
    public:
        virtual ~IEmitterAllocateCallback() = default;
        virtual void onAllocEmitter(sead::Heap* heap, Emitter* emitter, const sead::SafeString& name) = 0;
        virtual void onFreeEmitter(Emitter* emitter) = 0;
    };

    struct InitializeArg {
        /// The number of sound sources.
        s32 sound_source_num;
        /// The number of spatial calculators and the factory that creates them (nullptr: the default one).
        s32 spatial_calculator_num;
        ISpatialCalculatorFactory* spatial_calculator_factory;
        /// The number of spatial playing params.
        s32 spatial_playing_param_num;
    };

    Arbiter();
    ~Arbiter();

    /// The memory needed for the given number of emitters.
    static u32 getRequireEmitterCreateHeap(s32 emitter_num);

    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void finalize();
    void calc();
    void freeEmitter(Emitter* emitter);
    SoundSource* allocSoundSource();
    /// Creates an emitter on `heap` (the default heap of the arbiter if it is null).
    Emitter* allocEmitter(sead::Heap* heap, const sead::SafeString& name);
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
    /// Zero-initialized by the constructor; SoundSourceUnifier::allocSource puts it into the condition of non-looped sounds.
    s32 get_8() const { return _8; }

private:
    s32 _8;
    sead::OffsetList<Emitter> mActiveEmitters;
    sead::Heap* mEmitterHeap;
    s32 mNextSoundSourceId;
    sead::PtrArray<SoundSource> mSoundSourceBuffer;
    s32 mSoundSourceSearchStart;
    sead::OffsetList<SoundSource> mSoundSources;
    SpatialCalculatorPool* mSpatialCalculatorPool;
    SpatialPlayingParamPool* mSpatialPlayingParamPool;
    sead::CriticalSection mEmitterCS;
    sead::CriticalSection mSoundSourceCS;
    /// Taken around the calls into the sound sources.
    sead::CriticalSection mSoundSourceCallCS;
    IEmitterAllocateCallback* mEmitterAllocateCallback;
    u8* _140;
    s32 mEmitterNum;
    s32 _14c;
    u64 _150;
    sead::Vector2f _158;
    void* _160;
    void* _168;
    void* _170;
    void* _178;
    u8 _180;
    u8 _181[7];
    u64 _188;
    s32 _190;
    u8 _194;
};

}  // namespace aal
