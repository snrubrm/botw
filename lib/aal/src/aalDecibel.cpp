#include "aal/aalDecibel.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace aal::Decibel {

// 0x7100ba40d4
f32 toVolume(f32 decibel) {
    if (decibel < -90.309f)
        return 0.0f;
    return std::pow(10.0f, decibel * 0.05f);
}

// 0x7100ba4100
f32 toDecibel(f32 volume) {
    if (volume > 0.0f)
        return std::log10(volume) * 20.0f;
    return -90.4f;
}

// 0x7101407998
f32 toDecibelTable(f32 volume) {
    if (volume <= 0.0f)
        return -9030.9f;
    return std::log10(volume) * 2000.0f;
}

// NON_MATCHING: same instructions, the callee-saved register for the scaled decibels is d9 instead of d8.
// 0x71014079cc
f32 toVolumeTable(f32 decibel) {
    if (decibel < -9030.899f)
        return 0.0f;
    return sead::Mathf::expTable(decibel * 0.0005f * sead::Mathf::logTable(10.0f));
}

}  // namespace aal::Decibel
