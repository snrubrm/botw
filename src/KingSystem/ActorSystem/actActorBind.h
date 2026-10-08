#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}  // namespace gsys

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
    // Takes the bound actor like m4 (DgnObj_DLC_CogWheel2::m5 reads it from the argument; the base and
    // ModelBindInfo ignore it).
    virtual bool m5(BaseProc* proc) { return false; }
    virtual bool m6(BaseProc* proc);
    virtual bool m7(BaseProc* proc);
    virtual bool m8(BaseProc* proc);
    virtual void m9(BaseProc* proc);
    // Called with the object's own link `_8` by BindAction::m34 / BowChildCreate (after acquiring
    // the bound actor into it).
    virtual void m10(BaseProcLink* link) {}

    // Inline only (placeholder name): BindAction::m34 and BowChildCreate (0x71000cec68) acquire the
    // actor into _8 and call m10 through the vtable (not devirtualized there).
    void x(BaseProc* proc) {
        _8.acquire(proc, false);
        m10(&_8);
    }
    // Same with a link (PlayerStoleOpenBase::enter_).
    void x(const BaseProcLink& link) {
        _8 = link;
        m10(&_8);
    }

    // Returns the bound actor (looked up as `_20` if set, else as `proc`).
    Actor* sub_7100D3C5E0(BaseProc* proc);
    // 0x7100d3c770 (placeholder name): the model of the actor returned by sub_7100D3C5E0, or null.
    gsys::Model* sub_7100D3C770(BaseProc* proc);

    /* 0x08 */ BaseProcLink _8;
    /* 0x18 */ bool _18 = true;
    /* 0x20 */ BaseProc* _20 = nullptr;
};
KSYS_CHECK_SIZE_NX150(ActorBind, 0x28);

}  // namespace ksys::act
