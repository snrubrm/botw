#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "aal/aalFadeCurveType.h"
#include "aal/aalVirtualizeMode.h"

namespace aal {

class AssetInfo;
class MarkerController;
class SoundGroup;
class SoundParam;
class SoundSource;

/// A reference to a playing sound: the sound source and the id the source had when the handle
/// was set up (sound sources are reused; a handle whose id differs from the source's is stale).
class Handle {
public:
    Handle();

    /// The handle that does not refer to a sound (the functions that return a handle return it when there is none).
    static const Handle cInvalid;

    /// Returns the sound source if the handle is still valid (the ids match), nullptr otherwise.
    SoundSource* getSoundSource();
    const SoundSource* getSoundSource() const;
    /// Points the handle at a sound source (and takes over its current id).
    void attachSoundSource(SoundSource* source);

    // The other members forward to the sound source if the handle is still valid and do nothing (or return a
    // default value) otherwise.
    bool isEnabled() const;
    bool isActive() const;
    void stop(f32 fade_time, f32 release_time);
    void pause(bool pause, f32 fade_time);
    void pause(sead::BitFlag8 mask, bool pause, f32 fade_time);
    void setVolume(f32 volume);
    void setTrackVolume(sead::BitFlag32 tracks, f32 volume);
    void setPitch(f32 pitch);
    void setSpread(f32 spread);
    void setLfe(f32 lfe);
    void setLpf(f32 lpf);
    void setBiquadFilter(int index, f32 value);
    void setBiquadType(int type);
    void setBiquadValue(f32 value);
    void setFadeCurveType(FadeCurveType type);
    bool setStartDelayTime(f32 delay_time);
    bool setFadeInTime(f32 fade_in_time);
    bool setReleaseCurveType(FadeCurveType type);
    bool setVirtualizeMode(VirtualizeMode mode);
    bool isPaused() const;
    bool isPaused(sead::BitFlag8 mask) const;
    bool isVirtualized() const;
    u32 getPlaySamplePosition() const;
    f32 getPlayingTime() const;
    const AssetInfo* getAssetInfo() const;
    const char* getAssetName() const;
    SoundGroup* getSoundGroup() const;
    const sead::SafeString& getSoundGroupName() const;
    MarkerController* getMarkerController() const;
    f32 getDelayTime() const;
    SoundParam* getDefaultParamPtr();

private:
    SoundSource* mSoundSource = nullptr;
    u32 mId = 0;
};
static_assert(sizeof(Handle) == 0x10, "aal::Handle size mismatch");

}  // namespace aal
