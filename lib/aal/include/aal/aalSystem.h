#pragma once

#include <basis/seadTypes.h>
#include "aal/aalCurveReader.h"

namespace sead {
class AudioMgr;
class Camera;
class DrawContext;
class Heap;
class Projection;
class Viewport;
}

namespace aal {

class Arbiter;
class AttenuationMgr;
class FinalFxMgr;
class GroupMgr;
class ListenerMgr;
class Settings;
class ShapeMgr;
class SoundSourceUnifier;
class SDKFoundation;
class MemoryPoolManager;
class SpeakerBalanceUnifierMgr;

/// The aal system singleton. TODO: only the manager pointers read through aal::SystemAccessor are modeled.
class System {
public:
    static System* sInstance;

    /// 0x7100b7a098
    void setLoopAssetListReader(LoopAssetListReader& reader);

    /// 0x7100b7a0a4: draws nothing in the retail build.
    void drawInformation3D(sead::DrawContext* context, const sead::Camera& camera,
                           const sead::Projection& projection, const sead::Viewport& viewport) const;

    u8 _0[0x28];
    /// Cleared while the system does not play sounds (Emitter::emit fails then).
    bool mEnabled;
    u8 _29[7];
    Arbiter* mArbiter;
    Settings* mSettings;
    GroupMgr* mGroupMgr;
    ListenerMgr* mListenerMgr;
    AttenuationMgr* mAttenuationMgr;
    ShapeMgr* mShapeMgr;
    SpeakerBalanceUnifierMgr* mSpeakerBalanceUnifierMgr;
    SoundSourceUnifier* mSoundSourceUnifier;
    FinalFxMgr* mFinalFxMgr;
    u8 _78[0x10];
    SDKFoundation* mSDKFoundation;
    u8 _90[8];
    MemoryPoolManager* mMemoryPoolManager;
    /// The directory of the stream files.
    const char* mStreamFileRoot;
    u8 _a8[0xe8 - 0xa8];
    /// The heap of the debug tools (HostIO): the components that are created through HostIO are allocated on it.
    sead::Heap* mDebugHeap;
    u8 _f0[0x100 - 0xf0];
    LoopAssetListReader mLoopAssetListReader;
    /// The audio manager of the sound library (nullptr if the library is not used).
    sead::AudioMgr* mAudioMgr;
};

}  // namespace aal
