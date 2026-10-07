#pragma once

#include <prim/seadEnum.h>

namespace aal {

/// The parameter that a distance curve of an Attenuator drives (SpatialCalculator::calcDistReduction). The names are
/// guesses from how the results are used (the text table of the original has not been located).
SEAD_ENUM(DistanceParamTarget, Volume, Unk1, Filter, Spread, PriorityFactor)

}  // namespace aal
