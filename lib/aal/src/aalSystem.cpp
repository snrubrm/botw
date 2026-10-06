#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

System* System::sInstance;

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
