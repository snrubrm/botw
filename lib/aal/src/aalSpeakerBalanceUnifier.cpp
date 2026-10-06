#include "aal/aalSpeakerBalanceUnifier.h"
#include <prim/seadScopedLock.h>
#include "aal/aalArbiter.h"
#include "aal/aalEmitter.h"
#include "aal/aalIUnifiable.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

namespace {
// The name until the unifier is allocated (execOnAllocated).
const sead::SafeString sDefaultName = "NoName";
}  // namespace

// 0x7100b93264
SpeakerBalanceUnifier::ListenerSpeakerBalance::ListenerSpeakerBalance()
    : mVolume{}, mFaders{{SimpleTimedFader(1.0f), SimpleTimedFader(1.0f), SimpleTimedFader(1.0f),
                          SimpleTimedFader(1.0f), SimpleTimedFader(1.0f), SimpleTimedFader(1.0f)}} {
    reset();
}

void SpeakerBalanceUnifier::ListenerSpeakerBalance::reset() {
    mVolume[0] = {};
    for (SimpleTimedFader& fader : mFaders[0])
        fader.setValueImmediate(0.0f);
}

// 0x7100b92570
void SpeakerBalanceUnifier::ListenerSpeakerBalance::setSpeakerBalance(DeviceType device,
                                                                       const SpeakerChannelVolume& volume,
                                                                       f32 step) {
    for (s32 i = 0; i < 5; ++i) {
        mFaders[device][i].moveToTargetByStep(volume.volume[i], step);
        mVolume[device].volume[i] = mFaders[device][i].getValue();
    }
}

// 0x7100b91af8
SpeakerBalanceUnifier::SpeakerBalanceUnifier()
    : mInitialized(false), mAllocated(false), mNoUnifiable(true), mEmitter(nullptr),
      mEnvFxReduction(0.0f), mFilterReduction(0.0f), mPriorityReduction(1.0f), mLpf(0.0f),
      mFilterReduction2(0.0f), mEnvFxFader(1.0f), mDistFilterFader(1.0f), mAttenuator(nullptr),
      mInteriorMask(0xffff), mInteriorNum(0), mSpeakerBalanceMoveStep(0.0f), mEnvFxMoveStep(0.0f),
      mDistFilterMoveStep(0.0f), _130(0), _138(0), _140(0), _148(false), _149(false),
      mReductionVolumeMax(nullptr) {}

// 0x7100b91c48 (D1) / 0x7100b91df8 (D0) and the thunks 0x7100b91dbc / 0x7100b91e38
SpeakerBalanceUnifier::~SpeakerBalanceUnifier() {
    finalize();
}

// NON_MATCHING: same code, but the original loads the next node at the top of each iteration (the robust walk over the
// unifiables compiles with an extra address computation here).
// 0x7100b91c80
void SpeakerBalanceUnifier::finalize() {
    if (!mInitialized)
        return;

    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        for (auto& node : mUnifiables.robustRange())
            mUnifiables.erase(&node);
    }

    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].finalize();
    if (mAreas.isBufferReady())
        mAreas.freeBuffer();
    if (mListenerBalances.isBufferReady())
        mListenerBalances.freeBuffer();
    if (mExtSounds.isBufferReady())
        mExtSounds.freeBuffer();
    if (mReductionVolumeMax) {
        delete[] mReductionVolumeMax;
        mReductionVolumeMax = nullptr;
    }
    mInitialized = false;
}

// 0x7100b91e84
void SpeakerBalanceUnifier::initialize(s32 listener_num, sead::Heap* heap) {
    if (mInitialized)
        return;

    mAreas.tryAllocBuffer(listener_num, heap, 8);
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].initialize(heap);
    mListenerBalances.tryAllocBuffer(listener_num, heap, 8);
    mEnvFxFader.setValueImmediate(0.0f);
    mDistFilterFader.setValueImmediate(0.0f);
    setObjName(sDefaultName);
    _130 = 0;
    _138 = 0;
    _140 = 0;
    mInitialized = true;
}

// NON_MATCHING: as finalize (the robust walk over the unifiables).
// 0x7100b92048
void SpeakerBalanceUnifier::clearUnifiable() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& node : mUnifiables.robustRange())
        mUnifiables.erase(&node);
}

// 0x7100b924dc
void SpeakerBalanceUnifier::updateFaders_() {
    for (s32 i = 0; i < mListenerBalances.size(); ++i) {
        ListenerSpeakerBalance& balance = mListenerBalances[i];
        for (s32 j = 0; j < 5; ++j)
            balance.mFaders[0][j].calc();
    }
    mEnvFxFader.calc();
    mDistFilterFader.calc();
}

// 0x7100b926b0
void SpeakerBalanceUnifier::addUnifiable(IUnifiable* unifiable) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mUnifiables.pushBack(unifiable);
}

// NON_MATCHING: same code, the two temporaries (the list of the node, the address of the list) use swapped registers.
// 0x7100b9273c
void SpeakerBalanceUnifier::removeUnifiable(IUnifiable* unifiable) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    sead::TListNode<IUnifiable*>* node = unifiable;
    if (node->mList == &mUnifiables)
        mUnifiables.erase(node);
}

// 0x7100b927a8
void SpeakerBalanceUnifier::setRegisterCullingDistance(f32 distance) {
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].setRegisterCullingDistance(distance);
}

// 0x7100b928d4
void SpeakerBalanceUnifier::initializeExtSounds(s32 num, sead::Heap* heap) {
    if (num >= 1 && !mExtSounds.isBufferReady())
        mExtSounds.tryAllocBuffer(num, heap, 8);
}

// 0x7100b92970
bool SpeakerBalanceUnifier::addExtSoundSource(SoundSource* sound_source) {
    if (!isExtSoundSourceAddable(sound_source))
        return false;
    if (!mExtSounds.isBufferReady())
        return false;
    if (mExtSounds.size() < 1)
        return false;

    for (s32 i = 0; i < mExtSounds.size(); ++i) {
        if (mExtSounds[i].getSoundSource() == sound_source)
            return false;
    }

    for (s32 i = 0; i < mExtSounds.size(); ++i) {
        if (!mExtSounds[i].isEnabled()) {
            mExtSounds[i].attachSoundSource(sound_source);
            sound_source->setSpeakerBalanceSupplier(this);
            return true;
        }
    }
    return false;
}

// 0x7100b92a94
bool SpeakerBalanceUnifier::isExtSoundSourceAddable(SoundSource* sound_source) const {
    return sound_source && sound_source->mState <= 2 && !sound_source->mSpeakerBalanceSupplier;
}

// 0x7100b92ac4
void SpeakerBalanceUnifier::setAttenuator(Attenuator* attenuator) {
    mAttenuator = attenuator;
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].setAttenuator(attenuator);
}

// 0x7100b92b34
void SpeakerBalanceUnifier::setInteriorNum(s32 num) {
    mInteriorNum = num;
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].setInteriorNum(num);
}

// 0x7100b92ba4
void SpeakerBalanceUnifier::setSpread(f32 spread) {
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].setSpread(spread);
}

// 0x7100b92c18
void SpeakerBalanceUnifier::setListenerDirectivityEnabled(bool enabled) {
    for (s32 i = 0; i < mAreas.size(); ++i)
        mAreas[i].setListenerDirectivityEnabled(enabled);
}

// 0x7100b92c60
void SpeakerBalanceUnifier::setSpeakerBalanceMoveStep(f32 step) {
    if (step >= 0.0f)
        mSpeakerBalanceMoveStep = step * 255.0f;
}

// 0x7100b92c7c
void SpeakerBalanceUnifier::setEnvFxMoveStep(f32 step) {
    if (step >= 0.0f)
        mEnvFxMoveStep = step;
}

// 0x7100b92c8c
void SpeakerBalanceUnifier::setDistFilterMoveStep(f32 step) {
    if (step >= 0.0f)
        mDistFilterMoveStep = step;
}

// 0x7100b92fe8
void SpeakerBalanceUnifier::execOnAllocated(const sead::SafeString& name, sead::Heap* heap) {
    setObjName(name);
    mEmitter = SystemAccessor::getArbiter()->allocEmitter(heap, name);
    initParams_();
    mAllocated = true;
}

// NON_MATCHING: as finalize (the robust walk over the unifiables).
// 0x7100b93044
void SpeakerBalanceUnifier::initParams_() {
    if (mListenerBalances.isBufferReady()) {
        for (s32 i = 0; i < mListenerBalances.size(); ++i)
            mListenerBalances[i].reset();
    }

    mEnvFxReduction = 0.0f;
    mFilterReduction = 0.0f;
    mPriorityReduction = 0.0f;
    mLpf = 0.0f;
    mFilterReduction2 = 0.0f;
    mEnvFxFader.setValueImmediate(0.0f);
    mDistFilterFader.setValueImmediate(0.0f);
    mInteriorMask = 0xffff;
    mAttenuator = nullptr;
    _148 = false;
    _149 = false;
    mInteriorNum = 0;
    mSpeakerBalanceMoveStep = 0.0f;
    mEnvFxMoveStep = 0.0f;
    mDistFilterMoveStep = 0.0f;

    if (mAreas.isBufferReady()) {
        for (s32 i = 0; i < mAreas.size(); ++i)
            mAreas[i].initParams();
    }
}

// 0x7100b931a8
void SpeakerBalanceUnifier::execOnFree() {
    clearUnifiable();
    if (mEmitter) {
        SystemAccessor::getArbiter()->freeEmitter(mEmitter);
        mEmitter = nullptr;
    }
    if (mExtSounds.isBufferReady())
        mExtSounds.freeBuffer();
    mAllocated = false;
}

// 0x7100b9324c
f32 SpeakerBalanceUnifier::getReductionVolumeMax(s32 index) const {
    if (mReductionVolumeMax)
        return mReductionVolumeMax[index];
    return 1.0f;
}

// 0x7100b93484
void SpeakerBalanceUnifier::calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device,
                                               s32 index, f32 spread) {
    calcSpeakerBalance(volume, device, 0, index, spread);
}

// NON_MATCHING: same code; the original keeps the result at 0x18 of the frame (next to the handle) and stores the handle
// before it reads the result.
// 0x7100b9281c
Handle SpeakerBalanceUnifier::emit(const AssetInfo& asset, SoundSource::SetupInfo* setup, StartResult* result) {
    if (!mEmitter) {
        if (result)
            *result = static_cast<StartResult>(8);
        return Handle::cInvalid;
    }

    StartResult emit_result = StartResult::Success;
    Handle handle = mEmitter->emit(asset, setup, &emit_result);
    if (emit_result > StartResult::Success) {
        if (result)
            *result = emit_result;
        return Handle::cInvalid;
    }

    handle.getSoundSource()->setSpeakerBalanceSupplier(this);
    if (result)
        *result = StartResult::Success;
    return handle;
}

}  // namespace aal
