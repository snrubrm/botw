#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalHandle.h"
#include "aal/aalSoundParam.h"
#include "aal/aalSoundSource.h"
#include "aal/aalStartResult.h"
#include "aal/aalSpatialSetting.h"
#include "aal/aalActiveSoundLimiter.h"

namespace ksys::snd {
class Unk_SoundMgr48;
}

namespace aal {

class AssetInfo;
class IAssetInfoReadable;
class SoundSource;

/// Emits sounds (SoundSource) and keeps track of the ones that are playing.
/// TODO: incomplete (the SoundParam at +0x10 and the SpatialSetting at +0xa8 are not modeled; the constructor and
/// destructor are not decompiled).
class Emitter : public sead::hostio::Node {
    friend class Arbiter;
    friend class SoundSource;
    // Original 105590c initializes this emitter's SpatialSetting at +a8 directly.
    friend class ksys::snd::Unk_SoundMgr48;

public:
    Emitter();
    virtual ~Emitter();

    static u32 getRequiredMemSize();

    /// 0x7100b9ed70 / 0x7100b9ee40 (declared only)
    bool initialize(const sead::SafeString& name, sead::Heap* heap);
    void finalize();

    void calc();
    /// Whether any of the sound sources of the emitter is still playing.
    bool isActive() const;
    void removeSoundSource(SoundSource* sound_source);
    /// Stops all the sound sources of the emitter (negative fade times are ignored).
    void stop(f32 fade_time);
    /// Starts a sound with the asset; the result tells why it failed. Returns an invalid handle then.
    Handle emit(const AssetInfo& asset, SoundSource::SetupInfo* setup, StartResult* result);
    static bool searchAssetInfo(AssetInfo* asset_info, IAssetInfoReadable* reader, const sead::SafeString& name,
                                bool flag);
    void setDebugSolo(bool solo);
    void setDebugMute(bool mute);
    bool isDebugMuted() const;
    /// The spread (added to the spread of the sounds that are unified into one sound).
    f32 getSpread() const { return mSoundParam.getSpread(); }

private:
    void disconnectAllSoundSource_();

    bool mInitialized;
    SoundParam mSoundParam;
    sead::OffsetList<SoundSource>* mSoundSources;
    sead::CriticalSection mCS;
    /// The memory of the limiter.
    u8* mLimiterBuffer;
    ActiveSoundLimiter* mLimiter;
    SpatialSetting mSpatialSetting;
    /// The node in the list of the active emitters of the arbiter.
    sead::ListNode mArbiterNode;
    u8 _138[4];

    /// Bit 0: solo, bit 1: muted (a solo emitter is not muted).
    u8 mDebugFlags;
    u8 _13d[3];
    void* _140;
};

}  // namespace aal
