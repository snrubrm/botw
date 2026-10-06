#include "aal/aalArbiter.h"
#include <prim/seadScopedLock.h>
#include "aal/aalEmitter.h"
#include <basis/seadNew.h>
#include <new>
#include "aal/aalSoundSource.h"
#include "aal/aalSpatialPlayingParamPool.h"

namespace aal {

// NON_MATCHING: the original merges the two float stores (40.0f, 50.0f) into one 64-bit store.
// 0x7100b9df70
Arbiter::Arbiter()
    : _8(0), mEmitterHeap(nullptr), mNextSoundSourceId(1), mSoundSourceSearchStart(0),
      mSpatialCalculatorPool(nullptr), mSpatialPlayingParamPool(nullptr),
      mEmitterAllocateCallback(nullptr), _140(nullptr), mEmitterNum(0), _14c(0), _150(0),
      _158(40.0f, 50.0f), _160(nullptr), _168(nullptr), _170(nullptr), _178(nullptr),
      _180(0), _188(0), _190(0), _194(0) {}

// 0x7100b9e018
Arbiter::~Arbiter() {
    finalize();
}

// 0x7100b9e1bc
void Arbiter::initialize(const InitializeArg& arg, sead::Heap* heap) {
    mSoundSourceBuffer.allocBuffer(arg.sound_source_num, heap, 8);
    for (s32 i = 0; i < arg.sound_source_num; ++i) {
        auto* sound_source = new (heap, 8) SoundSource;
        sound_source->initialize(heap);
        mSoundSourceBuffer.pushBack(sound_source);
    }

    mSpatialCalculatorPool = new (heap, 8) SpatialCalculatorPool;
    if (mSpatialCalculatorPool)
        mSpatialCalculatorPool->initialize(arg.spatial_calculator_num, heap, arg.spatial_calculator_factory);

    mSpatialPlayingParamPool = new (heap, 8) SpatialPlayingParamPool;
    if (mSpatialPlayingParamPool)
        mSpatialPlayingParamPool->initialize(arg.spatial_playing_param_num, heap);

    mActiveEmitters.initOffset(offsetof(Emitter, mArbiterNode));
    mSoundSources.initOffset(offsetof(SoundSource, mArbiterNode));
    mNextSoundSourceId = 1;
    mSoundSourceSearchStart = 0;
}

// NON_MATCHING: same search; the original keeps the found index in a 64-bit induction variable and skips the store when nothing is found in the second loop.
// 0x7100b9e7f0
SoundSource* Arbiter::allocSoundSource() {
    sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCS);
    const s32 size = mSoundSourceBuffer.size();
    const s32 start = mSoundSourceSearchStart;
    s32 index = -1;
    s32 next_start = start;
    for (s32 i = start; i < size; ++i) {
        if (mSoundSourceBuffer(i)->mId == 0) {
            index = i;
            next_start = start + 1;
            break;
        }
    }
    if (index < 0) {
        for (s32 i = 0; i < start; ++i) {
            if (mSoundSourceBuffer(i)->mId == 0) {
                index = i;
                next_start = start >= size ? 0 : start + 1;
                break;
            }
        }
    }

    mSoundSourceSearchStart = next_start;
    if (static_cast<u32>(index) >= static_cast<u32>(size))
        return nullptr;

    SoundSource* sound_source = mSoundSourceBuffer[index];
    if (!sound_source)
        return nullptr;

    sound_source->mId = mNextSoundSourceId;
    mNextSoundSourceId = mNextSoundSourceId == -1 ? 1 : mNextSoundSourceId + 1;
    mSoundSources.pushBack(sound_source);
    return sound_source;
}

// NON_MATCHING: same calls and branches; the block layout differs and the registers of the emitter and the arbiter are swapped.
// 0x7100b9e648
Emitter* Arbiter::allocEmitter(sead::Heap* heap, const sead::SafeString& name) {
    if (!heap)
        heap = mEmitterHeap;

    if (heap) {
        Emitter* emitter = new (heap, std::nothrow) Emitter;
        if (emitter) {
            if (emitter->initialize(name, heap)) {
                ++mEmitterNum;
                if (mEmitterAllocateCallback)
                    mEmitterAllocateCallback->onAllocEmitter(heap, emitter, name);
                return emitter;
            }
            delete emitter;
        }
    }
    if (mEmitterAllocateCallback)
        mEmitterAllocateCallback->onAllocEmitter(heap, nullptr, name);
    return nullptr;
}

// 0x7100b9e744
void Arbiter::freeEmitter(Emitter* emitter) {
    if (!emitter)
        return;

    if (mEmitterAllocateCallback)
        mEmitterAllocateCallback->onFreeEmitter(emitter);

    sead::ScopedLock<sead::CriticalSection> lock(&mSoundSourceCallCS);
    emitter->finalize();
    delete emitter;
    --mEmitterNum;
}

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
