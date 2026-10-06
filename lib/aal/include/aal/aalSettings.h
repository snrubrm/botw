#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include "aal/aalDeviceType.h"
#include "aal/aalOutputMode.h"

namespace aal {

class OutputDevice;

/// How the speaker balance of the unified sounds is calculated. TODO: the values are not known.
enum class SpeakerBalanceMode : u32;

/// The settings of the aal system. TODO: incomplete: the vtable (offset 0), the output mode (0x8), the SDK
/// and the speaker balance modes (0x54) are not modeled.
class Settings {
public:
    Settings();
    virtual ~Settings();

    /// Calculates the output device.
    void calc();
    /// Also recalculates what the speaker balance unifiers have precalculated.
    void setSpeakerBalanceMode(OutputMode output_mode, SpeakerBalanceMode mode);
    SpeakerBalanceMode getCurrentSpeakerBalanceMode(DeviceType device) const;
    SpeakerBalanceMode getSpeakerBalanceMode(OutputMode output_mode) const {
        return mSpeakerBalanceModes[output_mode];
    }

    /// Ignored if `fps` is not positive.
    void setBaseFPS(f32 fps);
    /// Ignored if `rate` is not positive.
    void setFrameWaitIntervalStepRate(f32 rate);
    /// Ignored if `length` is not positive.
    void setLengthPerMeter(f32 length);
    /// 1 if the doppler mode is 1 (no pitch limit), the configured limit otherwise.
    f32 getDopplerPitchMin() const;
    f32 getDopplerPitchMax() const;

    /// The output device (the Switch only has the TV).
    OutputDevice* getOutputDevice(DeviceType device) const { return mOutputDevices[device]; }

    sead::SafeArray<OutputMode, 1> mOutputModes;
    u8 _c[4];
    sead::SafeArray<OutputDevice*, 1> mOutputDevices;
    u8 _18[4];
    f32 mBaseFPS;
    f32 mFrameWaitIntervalStepRate;
    /// The time that passes in one calculation step (the faders move by step * this value each calc).
    f32 mCalcTimeStep;
    /// The length of one meter in the game length unit (Meter::toLength).
    f32 mLengthPerMeter;
    f32 mLengthPerMeterSquared;
    /// The speed of sound in meters per second.
    f32 mSoundSpeed;
    /// The distance (in game length) that the sound travels in one frame.
    f32 mSoundDistancePerFrame;
    f32 mDopplerPitchMin;
    f32 mDopplerPitchMax;
    u32 mDopplerMode;
    u8 _44[0x54 - 0x44];
    sead::SafeArray<SpeakerBalanceMode, 3> mSpeakerBalanceModes;
};

}  // namespace aal
