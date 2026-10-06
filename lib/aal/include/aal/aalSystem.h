#pragma once

#include <basis/seadTypes.h>

namespace aal {

class Arbiter;
class AttenuationMgr;
class FinalFxMgr;
class GroupMgr;
class ListenerMgr;
class Settings;
class ShapeMgr;
class SoundSourceUnifier;
class SpeakerBalanceUnifierMgr;

/// The aal system singleton. TODO: only the manager pointers read through aal::SystemAccessor are modeled.
class System {
public:
    static System* sInstance;

    u8 _0[0x30];
    Arbiter* mArbiter;
    Settings* mSettings;
    GroupMgr* mGroupMgr;
    ListenerMgr* mListenerMgr;
    AttenuationMgr* mAttenuationMgr;
    ShapeMgr* mShapeMgr;
    SpeakerBalanceUnifierMgr* mSpeakerBalanceUnifierMgr;
    SoundSourceUnifier* mSoundSourceUnifier;
    FinalFxMgr* mFinalFxMgr;
};

}  // namespace aal
