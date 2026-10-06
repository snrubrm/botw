#pragma once

#include <basis/seadTypes.h>
#include <cstddef>

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "aal/aalFadeCurveType.h"
#include "aal/aalHandle.h"
#include "aal/aalSoundController.h"
#include "aal/aalSoundParam.h"
#include "aal/aalSpatialCalculator.h"
#include "aal/aalSpatialSetting.h"

namespace aal {

class AssetInfo;
class ISpeakerBalanceSupplier;
class MarkerController;
class SoundGroup;
enum class VirtualizeMode;

/// A playing sound (the object a Handle refers to).
/// TODO: incomplete. Only the members that are read through a Handle are declared; the rest of the
/// object (sound parameters, fade state, player pointers...) is not decompiled yet. The constructor
/// ends with a zeroed 0x50-byte block at 0x1a0, right after the spatial setting.
class SoundSource {
public:
    virtual ~SoundSource();

    /// Life cycle state: 0 is unused and 7 is finished; states up to 2 are the ones before playback
    /// starts (the start delay is counted down in state 1).
    u8 _8;
    /// volatile: the original reads it twice in isActive / getPlaySamplePosition, and reads it without using the value
    /// in setInteriorNum (`ldr wzr`), which is how a volatile read that is discarded compiles.
    volatile s32 mState;
    u32 mId;
    u8 _14;
    u8 _15;
    /// One bit per pause reason (Handle::pause uses all bits).
    sead::BitFlag8 mPauseFlags;
    /// Non-zero while the sound is virtualized.
    u8 mVirtualizedBy;
    f32 mPlayingTime;
    u8 _1c[0x24 - 0x1c];
    s32 mStartSamplePos;
    f32 mStartDelayTime;
    f32 mFadeInTime;
    FadeCurveType mFadeCurveType;
    u8 _34[0x38 - 0x34];
    /// The parameters the sound was set up with (Handle::getDefaultParamPtr) and the live ones.
    SoundParam mDefaultParam;
    SoundParam mParam;
    u8 _b8[0xd4 - 0xb8];
    /// Priority scale in [0, 1] (default 1; the constructor initialises 0xd4..0xe0 to 1).
    f32 mPriority;
    u8 _d8[0xe8 - 0xd8];
    SoundGroup* mSoundGroup;
    u8 _f0[0xf8 - 0xf0];
    /// The speaker balance supplier of the sound (SoundSource::setSpeakerBalanceSupplier).
    ISpeakerBalanceSupplier* mSpeakerBalanceSupplier;
    PlayingStateController* mPlayingStateController;
    u8 _108[0x120 - 0x108];
    SpatialSetting mSpatialSetting;
    /// Allocated from the spatial calculator pool when the sound is positioned in space; nullptr if none.
    SpatialCalculator* mSpatialCalculator;
    u8 _1a8[0x1b8 - 0x1a8];
    MarkerController* mMarkerController;

    // Non-virtual members, declared only (each is called through aal::Handle).
    bool setFadeInTime(f32 fade_in_time);
    bool setStartDelayTime(f32 delay_time);
    bool setReleaseCurveType(FadeCurveType type);
    /// 0x7100b77f94 (declared only)
    bool setReleaseTime(f32 release_time);
    /// 0x7100b781fc (declared only): the handle of the sound this one is unified into (an empty handle if none).
    Handle getUnifiedSoundHandle() const;
    bool setVirtualizeMode(VirtualizeMode mode);
    void stop(f32 fade_time, f32 release_time);
    void pause(bool pause, f32 fade_time);
    void pause(sead::BitFlag8 mask, bool pause, f32 fade_time);
    void setTrackVolume(sead::BitFlag32 tracks, f32 volume);
    bool isVirtualized() const;
    // 0x7100b78094 / 0x7100b780c8 / 0x7100b78048 / 0x7100b77e5c / 0x7100b781a4 / 0x7100b783b8
    bool setStreamRegionCallback(SoundController::StreamRegionCallback callback, void* user_data);
    void setIgnorePrefetch(bool ignore);
    bool setStartSamplePos(s32 position);
    void startPrepared();
    void setPriority(f32 priority);
    f32 getFadeInTimeIfBeforePlaying() const;
    u32 getPlaySamplePosition() const;
    const AssetInfo* getAssetInfo() const;
    const char* getAssetName() const;
    const sead::SafeString& getSoundGroupName() const;
};
static_assert(offsetof(SoundSource, mState) == 0xc, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mId) == 0x10, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSpatialSetting) == 0x120, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSpatialCalculator) == 0x1a0, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mPauseFlags) == 0x16, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mFadeCurveType) == 0x30, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mDefaultParam) == 0x38, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mParam) == 0x78, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSoundGroup) == 0xe8, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSpeakerBalanceSupplier) == 0xf8, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mPlayingStateController) == 0x100, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mPriority) == 0xd4, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mMarkerController) == 0x1b8, "aal::SoundSource layout mismatch");

}  // namespace aal
