#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace aal {

// The complete five-slot interface is shared by the native reverb argument
// table 25025b8 and delay argument table 251b538.
class FxInitializeArg {
    SEAD_RTTI_BASE(FxInitializeArg)
public:
    virtual ~FxInitializeArg() = default;
    virtual void save() {}
};
static_assert(sizeof(FxInitializeArg) == 8, "FxInitializeArg size");

}  // namespace aal
