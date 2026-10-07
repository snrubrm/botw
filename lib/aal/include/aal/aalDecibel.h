#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Conversions between a linear volume and decibels.
namespace Decibel {

/// 0 below -90.309 dB. 10 ^ (decibel / 20).
f32 toVolume(f32 decibel);
/// 20 * log10(volume); -90.4 for a volume that is not positive.
f32 toDecibel(f32 volume);
/// The same with the exp / log tables of sead and the decibels in hundredths (-9030.9 for a volume that is not
/// positive): the decibel value is `20 * 100 * log10(volume)`.
f32 toDecibelTable(f32 volume);
f32 toVolumeTable(f32 decibel);

}  // namespace Decibel

}  // namespace aal
