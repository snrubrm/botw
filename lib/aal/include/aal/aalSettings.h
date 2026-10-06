#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The settings of the aal system. TODO: only the members that are read by other classes are declared.
class Settings {
public:
    u8 _0[0x24];
    /// The time that passes in one calculation step (the faders move by step * this value each calc).
    f32 mCalcTimeStep;
    /// The length of one meter in the game length unit (Meter::toLength).
    f32 mLengthPerMeter;
};

}  // namespace aal
