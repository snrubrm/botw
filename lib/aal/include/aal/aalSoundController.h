#pragma once

#include <basis/seadTypes.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalFadeCurveType.h"
#include "aal/aalAssetInfo.h"
#include "aal/aalDeviceType.h"
#include "aal/aalTimedFader.h"
#include "aal/aalVirtualizeMode.h"

namespace sead {
class Heap;
}

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
    SoundHandle() : m_pSound(nullptr) {}

    /// 0x71033c3b0 (declared only)
    void DetachSound();

    detail::BasicSound* m_pSound;
};
}  // namespace nn::atk

namespace aal {


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
    /// 0x7100ba23f8: the priority (0 - 1) of the sound for the voice allocation of the sound library.
    void setChannelPriority(f32 priority);
    bool isInnerPaused() const;

    SoundController();
    virtual ~SoundController();

    void initialize(sead::Heap* heap);
    void finalize();
    void reset();
    void calc();
    bool start(f32 fade_time, bool prepare);
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

/// The playing state of a SoundSource (SoundSource +0x100): owns the SoundController and handles stopping,
/// virtualization (a virtualized sound is not played, but its position is advanced) and pausing.
/// State: 0 stopped, 1 playing, 2 releasing, 3 virtualized, 4 about to restart after the virtualization.
class PlayingStateController {
public:
    PlayingStateController();
    virtual ~PlayingStateController();

    void initialize(sead::Heap* heap);
    void finalize();
    void reset();
    bool start(bool prepare);
    void stopWithRelease();
    void stopForce();
    void preCalc();
    void calc();
    /// Returns whether the sound is virtualized (or stopped).
    bool virtualize();
    void unvirtualize();
    /// 0x7100ba028c (declared only): returns whether the wave asset was in use by this sound.
    bool execOnDestroyWaveAsset(u64 a, u64 b, bool c, bool d);
    /// 0x7100b9fd14 / 0x7100ba025c: a negative release time is ignored / the sample position of the sound
    /// (-1 if there is none).
    void setReleaseTime(f32 release_time);
    s32 getPlayingSamplePos() const;
    void pause(bool pause, f32 fade_time);
    void setVirtualizeMode(VirtualizeMode mode);

    SoundController* mSoundController = nullptr;
    s32 mState = 0;
    /// Written by setVirtualizeMode; 0 means the sound can not be virtualized (SoundSource::canVirtualize). The
    /// names of the modes are not known (1 is the default, 2 restarts the sound when it is unvirtualized).
    VirtualizeMode mVirtualizeMode = VirtualizeMode(1);
    bool mPaused = false;
    f32 mReleaseTime = 0.0f;
    f32 _20 = 0.0f;
    f32 mSamplePos = 0.0f;

private:
    /// Restarts a virtualized sound at the sample position; returns whether the sound plays again.
    bool restart_(u32 sample_pos, f32 fade_time);
    void updateVirtualPlayingPos_();

    sead::CriticalSection mCS;
};

}  // namespace aal
