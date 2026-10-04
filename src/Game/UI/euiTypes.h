#pragma once

#include <prim/seadEnum.h>

namespace eui {

// The two screens of the original (guess: TV / gamepad); the enumerator names are not known.
SEAD_ENUM(DrawTarget, _0, _1)

// A direction of the box cursor routes (up / down / left / right in some order; names not known)
SEAD_ENUM(Direction, _0, _1, _2, _3)

}  // namespace eui
