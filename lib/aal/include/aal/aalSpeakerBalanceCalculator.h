#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>

namespace aal {

struct SpeakerChannelVolume;
class Interior;
enum class SpeakerBalanceMode : u32;

/// Calculates the volumes of the speakers for a sound.
class SpeakerBalanceCalculator {
public:
    // Mode labels describe the native add (0) and maximum (1) merge behavior.
    SEAD_ENUM(Mode, Add, Max)

    /// 0x7100b86264: `angle_idx` is the direction of the sound in the units of
    /// OutputDevice::getSpeakerChannelAngleIdx.
    static void calculate(SpeakerChannelVolume* out, f32 volume, u32 angle_idx, f32 distance_rate, f32 spread,
                          f32 lfe, const Interior* interior, Mode mode, SpeakerBalanceMode balance_mode);
private:
    struct AngleSection {
        u32 lower;
        u32 upper;
    };
    static_assert(sizeof(AngleSection) == 8);
    static void calcSpread_(f32*, f32*, const AngleSection&, const AngleSection*,
                            f32, SpeakerBalanceMode);
    static void calcSpeakerBalanceFromAngleNoSpread_(SpeakerChannelVolume*, u32, f32,
                                                    const Interior&, Mode, SpeakerBalanceMode);
    static void calcSpeakerBalanceFromAngleNoSpreadStereo_(SpeakerChannelVolume*, u32, f32,
                                                          Mode, SpeakerBalanceMode);
    static void calcSpeakerBalanceFromAngleSpread_(SpeakerChannelVolume*, u32, f32, f32, f32,
                                                  const Interior&, Mode, SpeakerBalanceMode);
    static void calcSpeakerBalanceFromAngleSpreadStereo_(SpeakerChannelVolume*, u32, f32, f32,
                                                        f32, Mode, SpeakerBalanceMode);
};

}  // namespace aal
