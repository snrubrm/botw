#pragma once

#include <container/seadBuffer.h>
#include <container/seadTList.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalDeviceType.h"
#include "aal/aalHandle.h"
#include "aal/aalISpeakerBalanceSupplier.h"
#include "aal/aalNamedObj.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSpeakerBalanceUnifierArea.h"
#include "aal/aalSpeakerChannelVolume.h"
#include "aal/aalStartResult.h"
#include "aal/aalTimedFader.h"

namespace sead {
class Heap;
}

namespace aal {

class Attenuator;
class Emitter;
class IUnifiable;
class AssetInfo;

/// Plays one sound for several unifiable positions with a speaker balance that is calculated from all of them: the
/// sound is emitted from an Emitter of its own and its speaker balance is supplied by this object (the area of each
/// listener keeps the nearest registered position in each direction around the listener).
/// TODO: incomplete (calc, calcSpeakerBalance, emit and the unknown members are not decompiled).
class SpeakerBalanceUnifier : public ISpeakerBalanceSupplier, public FixedNamedObj<32> {
    SEAD_RTTI_OVERRIDE(SpeakerBalanceUnifier, ISpeakerBalanceSupplier)
    friend class SpeakerBalanceUnifierMgr;

public:
    /// The speaker balance of one listener: the target volume of each channel and the faders that move the actual
    /// volumes there.
    struct ListenerSpeakerBalance {
        ListenerSpeakerBalance();

        void reset();
        void setSpeakerBalance(DeviceType device, const SpeakerChannelVolume& volume, f32 step);

        SpeakerChannelVolume mVolume[DeviceType::size()];
        SimpleTimedFader mFaders[DeviceType::size()][6];
    };
    static_assert(sizeof(ListenerSpeakerBalance) == 0xa8, "aal::SpeakerBalanceUnifier::ListenerSpeakerBalance size mismatch");

    SpeakerBalanceUnifier();
    ~SpeakerBalanceUnifier() override;

    void initialize(s32 listener_num, sead::Heap* heap);
    void finalize();
    void calc();
    void clearUnifiable();
    void addUnifiable(IUnifiable* unifiable);
    void removeUnifiable(IUnifiable* unifiable);
    void setRegisterCullingDistance(f32 distance);
    /// 0x7100b9281c (declared only): starts the sound; the handle is the one of the sound that is played.
    Handle emit(const AssetInfo& asset, SoundSource::SetupInfo* setup, StartResult* result);
    void initializeExtSounds(s32 num, sead::Heap* heap);
    bool addExtSoundSource(SoundSource* sound_source);
    bool isExtSoundSourceAddable(SoundSource* sound_source) const;
    void setAttenuator(Attenuator* attenuator);
    void setInteriorNum(s32 num);
    void setSpread(f32 spread);
    void setListenerDirectivityEnabled(bool enabled);
    void setSpeakerBalanceMoveStep(f32 step);
    void setEnvFxMoveStep(f32 step);
    void setDistFilterMoveStep(f32 step);
    /// Called by the manager when the unifier is handed out / taken back.
    void execOnAllocated(const sead::SafeString& name, sead::Heap* heap);
    void execOnFree();

    void calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device, s32 index, f32 spread) override;
    void calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device, s32 index_a, s32 index_b,
                            f32 spread) override;
    f32 getEnvFxReduction() const override { return mEnvFxReduction; }
    f32 getFilterReduction() const override { return mFilterReduction + mFilterReduction2; }
    f32 getPriorityReduction() const override { return mPriorityReduction; }
    f32 getLpf() const override { return mLpf; }
    f32 getReductionVolumeMax(s32 index) const override;

private:
    void updateFaders_();
    void initParams_();

    /// The node in the list of the active unifiers of the SpeakerBalanceUnifierMgr.
    sead::ListNode mListNode;
    bool mInitialized;
    bool mAllocated;
    sead::Buffer<SpeakerBalanceUnifierArea> mAreas;
    sead::TList<IUnifiable*> mUnifiables;
    bool mNoUnifiable;
    Emitter* mEmitter;
    sead::Buffer<Handle> mExtSounds;
    sead::Buffer<ListenerSpeakerBalance> mListenerBalances;
    f32 mEnvFxReduction;
    f32 mFilterReduction;
    f32 mPriorityReduction;
    f32 mLpf;
    f32 mFilterReduction2;
    SimpleTimedFader mEnvFxFader;
    SimpleTimedFader mDistFilterFader;
    Attenuator* mAttenuator;

public:
    /// Which interiors the sounds are heard from (copied from the spatial calculator setting).
    u16 mInteriorMask;

private:
    s32 mInteriorNum;
    f32 mSpeakerBalanceMoveStep;
    f32 mEnvFxMoveStep;
    f32 mDistFilterMoveStep;
    u64 _130;
    u64 _138;
    u64 _140;
    bool _148;
    bool _149;
    sead::CriticalSection mCS;
    f32* mReductionVolumeMax;
};

}  // namespace aal
