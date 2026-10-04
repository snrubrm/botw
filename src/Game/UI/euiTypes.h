#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>

namespace eui {

// The two screens of the original (guess: TV / gamepad); the enumerator names are not known.
SEAD_ENUM(DrawTarget, _0, _1)

// A direction of the box cursor routes (up / down / left / right in some order; names not known)
SEAD_ENUM(Direction, _0, _1, _2, _3)

// 0x7100bed2bc: the angle (radians) of a box cursor route direction
f32 GetRadAngleOfDirection(Direction direction);

}  // namespace eui
