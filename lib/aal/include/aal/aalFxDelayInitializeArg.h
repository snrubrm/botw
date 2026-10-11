#pragma once

#include <basis/seadTypes.h>
#include "aal/aalFxInitializeArg.h"

namespace aal {

class FxDelayInitializeArg : public FxInitializeArg {
    SEAD_RTTI_OVERRIDE(FxDelayInitializeArg, FxInitializeArg)
public:
    FxDelayInitializeArg();

    // Native FxDelay::initialize 12cc1f0 uses this limit for the delay buffer.
    f32 mMaxDelay;
};
static_assert(sizeof(FxDelayInitializeArg) == 0x10, "FxDelayInitializeArg size");

}  // namespace aal
