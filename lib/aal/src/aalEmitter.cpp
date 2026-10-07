#include "aal/aalEmitter.h"
#include <basis/seadNew.h>
#include <heap/seadHeap.h>
#include <prim/seadScopedLock.h>
#include "aal/aalArbiter.h"
#include "aal/aalAssetInfo.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: the original zeroes the bytes at 0x135..0x13c with one unaligned 64-bit store.
// 0x7100b9ec94
Emitter::Emitter() : mInitialized(false), mSoundSources(nullptr), mLimiterBuffer(nullptr), mLimiter(nullptr) {
    mDebugFlags = 0;
    _138[0] = 0;
    _140 = nullptr;
    mArbiterNode = {};
}

// 0x7100b9ecf4 (D2) / 0x7100b9ed2c (D0)
Emitter::~Emitter() = default;

// 0x7100b9ed70
bool Emitter::initialize(const sead::SafeString&, sead::Heap* heap) {
    if (mInitialized)
        return true;

    heap->getMaxAllocatableSize(8);
    mSoundSources = new (heap, std::nothrow) sead::OffsetList<SoundSource>;
    if (!mSoundSources)
        return false;
    mSoundSources->initOffset(offsetof(SoundSource, mEmitterNode));

    heap->getMaxAllocatableSize(8);
    mLimiterBuffer = new (heap, std::nothrow) u8[LimiterUtil::getMaxActiveSoundLimiterSize()];
    if (!mLimiterBuffer) {
        if (mSoundSources)
            delete mSoundSources;
        return false;
    }

    mSpatialSetting.reset();
    mInitialized = true;
    return true;
}

// 0x7100b9eef0
void Emitter::disconnectAllSoundSource_() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mSoundSources) {
        for (SoundSource& sound_source : mSoundSources->robustRange()) {
            sound_source.execOnFinalizeEmitter();
            if (mSoundSources->indexOf(&sound_source) >= 0)
                mSoundSources->erase(&sound_source);
        }
    }
}

// 0x7100b9eff0
Handle Emitter::emit(const AssetInfo& asset, SoundSource::SetupInfo* setup, StartResult* result) {
    if (!System::sInstance->mEnabled) {
        if (result)
            *result = static_cast<StartResult>(2);
        return Handle::cInvalid;
    }
    if (!asset.isValid())
        return Handle::cInvalid;

    SoundSource* sound_source = System::sInstance->mArbiter->allocSoundSource();
    if (!sound_source) {
        if (result)
            *result = static_cast<StartResult>(7);
        return Handle::cInvalid;
    }

    // volatile: the original stores the result to the stack and reads it back once.
    volatile StartResult volatile_result = sound_source->setup(asset, setup);
    const StartResult start_result = volatile_result;
    if (start_result > StartResult::Success) {
        System::sInstance->mArbiter->freeSoundSource(sound_source);
        if (result)
            *result = start_result;
        return Handle::cInvalid;
    }

    sound_source->mSpatialSetting.setPositioned(mSpatialSetting.isPositioned());
    sound_source->mSpatialSetting.setPositionFollow(mSpatialSetting.isPositionFollow());
    if (mSpatialSetting.isPositioned())
        sound_source->mSpatialSetting.setSpatialCalculatorSetting(mSpatialSetting.getSpatialCalculatorSetting());

    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        if (mSoundSources)
            mSoundSources->pushBack(sound_source);
        sound_source->mEmitter = this;
        SystemAccessor::getArbiter()->appendToActiveEmitterList(this);
    }

    Handle handle;
    handle.attachSoundSource(sound_source);
    if (result)
        *result = StartResult::Success;
    return handle;
}

// 0x7100b9f160
void Emitter::stop(f32 fade_time) {
    if (fade_time >= 0.0f && mSoundSources) {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        for (SoundSource& sound_source : mSoundSources->robustRange())
            sound_source.stop(fade_time, 0.0f);
    }
}

// 0x7100b9f264
void Emitter::removeSoundSource(SoundSource* sound_source) {
    if (!sound_source)
        return;

    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        if (mSoundSources && mSoundSources->indexOf(sound_source) >= 0)
            mSoundSources->erase(sound_source);
    }

    if (!isActive())
        SystemAccessor::getArbiter()->removeFromActiveEmitterList(this);
}

// NON_MATCHING: the original does not mask the bool argument that is passed on.
// 0x7100b9f33c
bool Emitter::searchAssetInfo(AssetInfo* asset_info, IAssetInfoReadable* reader, const sead::SafeString& name,
                              bool flag) {
    if (name.getStringTop()[0] != sead::SafeString::cNullChar && reader) {
        if (reader->readAssetInfo(asset_info, name, flag))
            return true;
    }
    return false;
}

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
