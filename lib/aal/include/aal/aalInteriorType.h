#pragma once

#include <prim/seadEnum.h>

namespace aal {

// Native Interior::create uses the ordinary SEAD_ENUM conversion protocol.
SEAD_ENUM(InteriorType, Invalid, Stereo, Surround5point1ch, Surround4point1ch, Square, Wide)

}  // namespace aal
