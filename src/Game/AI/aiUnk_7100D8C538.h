#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// 0x7100d8c538 (declared only): forwards to 0x7100d8b080 with the CameraMgr's look-at camera (false when there
// is none): a view test of `pos` with two float tolerances (used as `!sub_7100D8C538(pos, 0.1, dist)` by the
// out-of-screen checks). Placeholder name.
bool sub_7100D8C538(const sead::Vector3f& pos, f32 a2, f32 a3);

// 0x7100d8c594 (CSV name visibilityCheckMaybe; declared only; CSV renamed): forwards to 0x7100d8b1f4 with the
// CameraMgr's look-at camera (false when there is none).
bool visibilityCheckMaybe(const sead::Vector3f& pos, f32 radius);

namespace cam {
// 0x7100d8c6ac (CSV name; declared only): writes the look-at camera's position (or the default position when
// there is no camera) to `out`; returns whether a camera exists.
bool getCameraPositionMaybe(sead::Vector3f* out);
}  // namespace cam
