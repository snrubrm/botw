#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class BaseProc;

// Name from the CSV (ActorBind::ctor 0x7100d3c5a0): binds an actor to another one (abstract).
// vtable 0x71024dae60 (11 slots; slot 4 pure). Base of ModelBindInfo.
// TODO: incomplete.
class ActorBind {
    SEAD_RTTI_BASE(ActorBind)
public:
    ActorBind();
    virtual ~ActorBind() = default;

    virtual bool m4(BaseProc* proc) = 0;
    virtual bool m5() { return false; }
    virtual bool m6(BaseProc* proc);
    virtual bool m7(BaseProc* proc);
    virtual bool m8(BaseProc* proc);
    virtual void m9(BaseProc* proc);
    virtual void m10() {}

    // Returns the bound actor (looked up as `_20` if set, else as `proc`).
    Actor* sub_7100D3C5E0(BaseProc* proc);

    /* 0x08 */ BaseProcLink _8;
    /* 0x18 */ bool _18 = true;
    /* 0x20 */ BaseProc* _20 = nullptr;
};
KSYS_CHECK_SIZE_NX150(ActorBind, 0x28);

}  // namespace ksys::act
