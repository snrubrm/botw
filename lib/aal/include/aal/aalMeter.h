#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace aal {

/// Conversions between meters and the length unit of the game (the scale is in aal::Settings).
namespace Meter {
f32 toLength(f32 meter);
f32 toMeter(f32 length);
sead::Vector3f toLength(const sead::Vector3f& meter);
}  // namespace Meter

}  // namespace aal
