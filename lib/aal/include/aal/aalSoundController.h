#pragma once

#include <basis/seadTypes.h>
#include "aal/aalFadeCurveType.h"
#include "aal/aalAssetInfo.h"
#include "aal/aalDeviceType.h"
#include "aal/aalTimedFader.h"

namespace nn::atk {
enum StreamRegionCallbackResult : int;
struct StreamRegionCallbackParam;

namespace detail {
/// TODO: only the members aal::SoundController uses are declared.
class BasicSound {
public:
    void SetPitch(f32 pitch);
    void SetLpfFreq(f32 lpf_freq);
    bool IsPause() const;
    void StartPrepared();
    void Pause(bool pause, int fade_frames);
};
}  // namespace detail

/// A handle to a playing sound (the original header's SoundHandle). TODO: partial.
class SoundHandle {
public:
    /// 0x71033c3b0 (declared only)
    void DetachSound();

    detail::BasicSound* m_pSound;
};
}  // namespace nn::atk

namespace aal {

enum class VirtualizeMode;

/// Controls the nn::atk sound of a SoundSource. TODO: only the members SoundSource forwards to are declared.
class SoundController {
public:
    using StreamRegionCallback =
        nn::atk::StreamRegionCallbackResult (*)(nn::atk::StreamRegionCallbackParam*, void*);

    /// 0x7100ba1d64 / 0x7100ba2058 / 0x7100ba2060 / 0x7100ba2068 / 0x7100ba2070 (declared only)
    void startPrepared();
    void setFadeCurveType(FadeCurveType type);
    void setStartSampleOffset(u32 offset);
    void setStreamRegionCallback(StreamRegionCallback callback, void* user_data);
    void setIgnorePrefetch(bool ignore);
    /// 0x7100ba248c (declared only)
    s32 getPlayingSamplePos() const;
    /// 0x7100ba2098 / 0x7100ba21e8 / 0x7100ba255c: forwarded to the nn::atk sound if there is one (the low pass is a
    /// negated frequency).
    void setPitch(f32 pitch);
    void setLpf(f32 lpf);
    bool isInnerPaused() const;

    SoundController();
    virtual ~SoundController();

    void finalize();
    /// Fades the sound out; the controller counts as released (state 3) once the fade has been started.
    void release(f32 fade_time);
    void pause(bool pause, f32 fade_time);

    /// 0x7100ba228c: static; the output line is a bit mask and bit 0 is the main (TV) output
    static bool checkDeviceEnabledOnOutputLine(DeviceType device, u32 output_line);

    /// 0 while the sound is not attached (SoundSource::isAttachedSound); pause() toggles 1 / 2 and release() sets 3.
    u32 mState = 0;
    FadeCurveType mFadeCurveType;
    u32 mStartSampleOffset = 0;
    u8 _14[4];
    StreamRegionCallback mStreamRegionCallback = nullptr;
    void* mStreamRegionUserData = nullptr;
    f32 _28 = 1.0f;
    s32 mChannelPriority = 127;
    AssetInfo* mAssetInfo = nullptr;
    SimpleTimedFader* mFader = nullptr;
    nn::atk::SoundHandle* mSoundHandle = nullptr;
};

/// The playing state of a SoundSource (SoundSource +0x100). TODO: only the controller pointer is modeled.
class PlayingStateController {
public:
    /// 0x7100b9fd14 / 0x7100ba025c: a negative release time is ignored / the sample position of the sound
    /// (-1 if there is none).
    void setReleaseTime(f32 release_time);
    s32 getPlayingSamplePos() const;
    /// 0x7100b9fdf4 / 0x7100ba0228 (declared only)
    void stopForce();
    void pause(bool pause, f32 fade_time);
    void setVirtualizeMode(VirtualizeMode mode);

    u8 _0[8];
    SoundController* mSoundController;
    u32 mState;
    /// Written by setVirtualizeMode; 0 means the sound can not be virtualized (SoundSource::canVirtualize).
    VirtualizeMode mVirtualizeMode;
    u8 _18[0x1c - 0x18];
    f32 mReleaseTime;
    u8 _20[0x24 - 0x20];
    f32 mSamplePos;
};

}  // namespace aal
