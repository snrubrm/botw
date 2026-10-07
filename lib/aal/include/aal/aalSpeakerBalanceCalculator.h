#pragma once

#include <basis/seadTypes.h>

namespace aal {

struct SpeakerChannelVolume;
class Interior;
enum class SpeakerBalanceMode : u32;

/// Calculates the volumes of the speakers for a sound. TODO: only `calculate` is declared.
class SpeakerBalanceCalculator {
public:
    /// The meaning of the modes is not known (the sound sources use 0).
    enum class Mode : u32 {};

    /// 0x7100b86264 (declared only): `angle_idx` is the direction of the sound in the units of
    /// OutputDevice::getSpeakerChannelAngleIdx.
    static void calculate(SpeakerChannelVolume* out, f32 volume, u32 angle_idx, f32 distance_rate, f32 spread,
                          f32 lfe, const Interior* interior, Mode mode, SpeakerBalanceMode balance_mode);
};

}  // namespace aal
