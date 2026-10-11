#pragma once

#include <basis/seadTypes.h>
#include "aal/aalFxInitializeArg.h"

namespace aal {

class FxReverbI3DL2InitializeArg : public FxInitializeArg {
    SEAD_RTTI_OVERRIDE(FxReverbI3DL2InitializeArg, FxInitializeArg)
public:
    FxReverbI3DL2InitializeArg();

    // Native initialize 1051ef0 consumes these five constructor parameters
    // as maximum buffer delays, diffusion percentage and delay-table index.
    f32 mMaxReflectionsDelay;
    f32 mMaxReverbDelay;
    f32 mMinDiffusion;
    f32 mMaxEarlyReflectionDelay;
    s32 mDelayTableIndex;
};
static_assert(sizeof(FxReverbI3DL2InitializeArg) == 0x20, "FxReverbI3DL2InitializeArg size");

}  // namespace aal
