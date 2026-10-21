#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"
#include <audio/seadAudioMgr.h>
#include <nn/atk/SoundSystem.h>
#include "aal/aalMemoryPoolManager.h"
#include "aal/aalSDKFoundation.h"

namespace aal {

System* System::sInstance;

// 0x7100b79f34
void System::calc(int voice_command_frames) {
    preCalc();
    if (mMemoryPoolManager)
        mMemoryPoolManager->flushMemoryPoolAcquireRequest();
    if (mSDKFoundation)
        mSDKFoundation->calc();
    if (mMemoryPoolManager)
        mMemoryPoolManager->flushMemoryPoolReleaseRequest();
    if (mAudioMgr)
        mAudioMgr->calc();
    if (voice_command_frames > 0)
        nn::atk::SoundSystem::VoiceCommandProcess(voice_command_frames);
}

// 0x7100b7a098
void System::setLoopAssetListReader(LoopAssetListReader& reader) {
    mLoopAssetListReader = reader;
}

// 0x7100b7a044
const LoopAssetListReader* System::getLoopAssetListReader() const {
    if (mDevReaderMgr) {
        const auto& readers = mDevReaderMgr->mReaders;
        const LoopAssetListReader* reader = readers.unsafeGet(readers.size() - 1);
        if (reader->hasEntries())
            return readers.empty() ? nullptr : reader;
    }
    return &mLoopAssetListReader;
}

// 0x7100b7a0a4
void System::drawInformation3D(sead::DrawContext*, const sead::Camera&, const sead::Projection&,
                               const sead::Viewport&) const {}

// 0x7100b7a134
System* SystemAccessor::getSystem() {
    return System::sInstance;
}

// 0x7100b7a144
Settings* SystemAccessor::getSettings() {
    if (auto* system = getSystem())
        return system->mSettings;
    return nullptr;
}

// 0x7100b7a164
GroupMgr* SystemAccessor::getGroupMgr() {
    if (auto* system = getSystem())
        return system->mGroupMgr;
    return nullptr;
}

// 0x7100b7a184
Arbiter* SystemAccessor::getArbiter() {
    if (auto* system = getSystem())
        return system->mArbiter;
    return nullptr;
}

// 0x7100b7a1a4
ListenerMgr* SystemAccessor::getListenerMgr() {
    if (auto* system = getSystem())
        return system->mListenerMgr;
    return nullptr;
}

// 0x7100b7a1c4
AttenuationMgr* SystemAccessor::getAttenuationMgr() {
    if (auto* system = getSystem())
        return system->mAttenuationMgr;
    return nullptr;
}

// 0x7100b7a1e4
ShapeMgr* SystemAccessor::getShapeMgr() {
    if (auto* system = getSystem())
        return system->mShapeMgr;
    return nullptr;
}

// 0x7100b7a204
SpeakerBalanceUnifierMgr* SystemAccessor::getSpeakerBalanceUnifierMgr() {
    if (auto* system = getSystem())
        return system->mSpeakerBalanceUnifierMgr;
    return nullptr;
}

// 0x7100b7a224
SoundSourceUnifier* SystemAccessor::getSoundSourceUnifier() {
    if (auto* system = getSystem())
        return system->mSoundSourceUnifier;
    return nullptr;
}

// 0x7100b7a244
FinalFxMgr* SystemAccessor::getFinalFxMgr() {
    if (auto* system = getSystem())
        return system->mFinalFxMgr;
    return nullptr;
}

}  // namespace aal
