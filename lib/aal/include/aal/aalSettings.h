#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include "aal/aalDeviceType.h"

namespace aal {

class OutputDevice;

/// The settings of the aal system. TODO: incomplete: the vtable (offset 0), the output mode (0x8), the SDK
/// and the speaker balance modes (0x54) are not modeled.
class Settings {
public:
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

    u8 _0[0x10];
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
};

}  // namespace aal
