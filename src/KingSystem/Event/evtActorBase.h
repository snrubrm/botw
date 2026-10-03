#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::evt {

// Placeholder for the event-side actor (CSV evt::ActorBase; 0x1d0-byte evt::Actor derives from it, ctor 0x7100da7ed8
// takes an ActorBinding). Only the vtable layout (slots 0-12) and the BaseProcLink at +0x8 are modelled so far.
class ActorBase {
public:
    SEAD_RTTI_BASE(ActorBase)

    virtual ~ActorBase();
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void play() = 0;
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;

    /* 0x8 */ act::BaseProcLink mLink;
};

}  // namespace ksys::evt
