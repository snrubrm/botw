#include "KingSystem/Sound/sndSound.h"
#include <aal/aalAttenuationMgr.h>
#include <aal/aalSpeakerBalanceUnifierMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/Actor/actSoundSystemActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// TU 0x710102c1d8..0x71010349dc in the original (static initialiser 0x710102c1a4 ends the previous TU): also
// Unk_SoundMgr38_18 (0x710102cfdc..) and Unk_SoundMgr38_10 (0x7101031010..).

Unk_SoundMgr38_8::Unk_SoundMgr38_8() = default;

Unk_SoundMgr38_8::~Unk_SoundMgr38_8() {
    sub_710102C27C();
}

void Unk_SoundMgr38_8::sub_710102C27C() {
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
    if (mUnifier) {
        aal::SystemAccessor::getSpeakerBalanceUnifierMgr()->freeSpeakerBalanceUnifier(mUnifier);
        mUnifier = nullptr;
    }
    mPositions.freeBuffer();
}

void Unk_SoundMgr38_8::sub_710102C388(sead::Heap* heap) {
    mPositions.tryAllocBuffer(50, heap);
    mUnifier =
        aal::SystemAccessor::getSpeakerBalanceUnifierMgr()->allocSpeakerBalanceUnifier("ForestShake", nullptr);
    if (mUnifier) {
        mUnifier->initializeExtSounds(8, heap);
        if (auto* mgr = aal::SystemAccessor::getAttenuationMgr()) {
            auto* attenuator = mgr->getDefaultAttenuator();
            mUnifier->setAttenuator(attenuator);
        }
        mUnifier->setSpeakerBalanceMoveStep(2.0f);
        mUnifier->setEnvFxMoveStep(2.0f);
        mUnifier->setDistFilterMoveStep(2.0f);
        mUnifier->setTotalVolumeLimitEnabled(true);
    }
    _60 = new (heap) xlink2::HandleSLink;
}

void Unk_SoundMgr38_8::sub_710102C4B0() {
    if (!_68 || !mProcHandle.isAllocatedOrFailed())
        return;
    if (!mProcHandle.isProcReady())
        return;
    if (auto* proc = mProcHandle.getProc()) {
        mTree = sead::DynamicCast<uking::act::SoundSystemActor>(proc);
        mTree->getActorFlags2().set(act::Actor::ActorFlag2::NoDistanceCheck);
    }
    mProcHandle.releaseAndWakeProc();
}

// NON_MATCHING: the original computes the handle test as a value before the count check and reloads the event in the
// fade and the second test.
// Plays the forest shake sound while positions are in use (fades it out otherwise) and unifies its speaker balance.
void Unk_SoundMgr38_8::sub_710102C5AC() {
    auto lock = sead::makeScopedLock(mCS);
    auto* handle = _60;
    const bool active = handle->isActive();
    if (mPositions.size() > 0) {
        if (!active && mTree && handle) {
            *_60 = eft::searchAndEmitSLink(mTree, "ForestShake", false);
            if (_60->isActive())
                _60->getEvent()->resetFlagBit(1);
        }
    } else if (handle && active) {
        handle->fade(60);
    }

    if (!_60->isActive())
        return;
    auto* executor = static_cast<xlink2::EventSLink*>(_60->getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* source = executor->getHandle()->getSoundSource();
    if (!source || !mUnifier->isExtSoundSourceAddable(source))
        return;
    mUnifier->addExtSoundSource(source);
    source->setFadeInTime(1.0);
    source->setReleaseTime(1.0);
    const auto& setting = source->mSpatialSetting.getCalculatorSetting();
    mUnifier->setAttenuator(setting.attenuator);
    mUnifier->setListenerDirectivityEnabled(setting.flags & 0x20);
}

void Unk_SoundMgr38_8::sub_710102C7C0(sead::Heap* heap, act::ActorCreator* creator) {
    if (!mTree)
        creator->requestCreateActor("EnvSoundTree", heap, &mProcHandle, nullptr, nullptr, 1);
    _50 = 0;
}

void Unk_SoundMgr38_8::sub_710102C810() {
    _68 = true;
}

void Unk_SoundMgr38_8::sub_710102C81C() {
    if (_60)
        _60->fade(30);
    _68 = false;
}

void Unk_SoundMgr38_8::sub_710102C594() {
    if (_68 && mTree)
        sub_710102C5AC();
}

// NON_MATCHING: the original stores the zeroed position z before the vtable load (scheduling only).
Unk_71025018c0* Unk_SoundMgr38_8::sub_710102C924() {
    if (!mPositions.isBufferReady())
        return nullptr;
    auto lock = sead::makeScopedLock(mCS);
    auto* position = mPositions.emplaceBack();
    if (position)
        mUnifier->addUnifiable(position);
    return position;
}

void Unk_SoundMgr38_8::sub_710102C9E8(void* handle) {
    if (!handle || !mPositions.isBufferReady())
        return;
    auto* position = static_cast<Unk_71025018c0*>(handle);
    auto lock = sead::makeScopedLock(mCS);
    mUnifier->removeUnifiable(position);
    mPositions.erase(position);
}

void Unk_SoundMgr38_8::sub_710102C8F8() {
    mProcHandle.deleteProc();
    mTree = nullptr;
    _68 = false;
}

void Unk_SoundMgr38_18::sub_710102EB9C() {}

void Unk_SoundMgr38_18::sub_710102EE40() {
    _9627 = true;
    _9624 = true;
    _9629 = true;
}

void Unk_SoundMgr38_10::sub_71010333E0() {
    _10c1 = true;
}

// NON_MATCHING: the two reset loops are strength-reduced to pointer loops here (the original keeps an
// index compare and a separately materialised float constant).
void Unk_SoundMgr38_10::sub_7101032870() {
    if (!_10c1 || !_18)
        return;

    sub_7101032940();

    for (s32 i = 0; i < 32; ++i) {
        mPositionActive[i] = false;
        mUnifier->removeUnifiable(&mPositions[i]);
    }

    _75c = 0.0f;
    _774 = 0.0f;
    for (s32 i = 0; i < 32; ++i) {
        _e88[i] = false;
        _788[i]._28[0] = 100000000.0f;
        _788[i]._28[1] = 100000000.0f;
        _788[i]._28[2] = 100000000.0f;
    }
}

// NON_MATCHING: same loop lowering as sub_7101032870.
void Unk_SoundMgr38_10::sub_710103362C() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);

    mProcHandle.deleteProc();
    _18 = nullptr;
    _758 = false;
    _10c0 = false;
    _18f8 = false;

    for (s32 i = 0; i < 32; ++i) {
        mPositionActive[i] = false;
        mUnifier->removeUnifiable(&mPositions[i]);
    }

    _75c = 0.0f;
    _774 = 0.0f;
    for (s32 i = 0; i < 32; ++i) {
        _e88[i] = false;
        _788[i]._28[0] = 100000000.0f;
        _788[i]._28[1] = 100000000.0f;
        _788[i]._28[2] = 100000000.0f;
    }

    _10c1 = false;
}

}  // namespace ksys::snd

Unk_7102501910::~Unk_7102501910() = default;

void Unk_7102501910::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}

Unk_7102501980::~Unk_7102501980() = default;

void Unk_7102501980::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}

Unk_7102501f10::~Unk_7102501f10() = default;

void Unk_7102501f10::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}
