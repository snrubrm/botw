#pragma once

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
class System;

/// Static access to the parts of the aal system singleton (all of them are nullptr if there is no system).
class SystemAccessor {
public:
    static System* getSystem();
    static Settings* getSettings();
    /// The group manager of the system, nullptr if there is no system.
    static GroupMgr* getGroupMgr();
    static Arbiter* getArbiter();
    static ListenerMgr* getListenerMgr();
    static AttenuationMgr* getAttenuationMgr();
    static ShapeMgr* getShapeMgr();
    static SpeakerBalanceUnifierMgr* getSpeakerBalanceUnifierMgr();
    static SoundSourceUnifier* getSoundSourceUnifier();
    static FinalFxMgr* getFinalFxMgr();
};

}  // namespace aal
