#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class BaseProc;
}

namespace ksys::evt {

// Placeholder name (from the CSV entry BaseProcLinkForEvent::ctorWithCallArg): the event call
// arguments that EventMgr::callEvent (0x7100db0c44) and BaseProcLinkForEvent::init take. The
// matrix is left uninitialised by callers that don't use it.
struct CallArg {
    /* 0x00 */ sead::Matrix34f _0;
    /* 0x30 */ bool _30 = false;
    /* 0x31 */ bool _31 = false;
    /* 0x32 */ bool _32 = false;
    /* 0x33 */ bool _33 = false;
    /* 0x38 */ const Metadata* metadata = nullptr;
    /* 0x40 */ void* _40 = nullptr;
    /* 0x48 */ act::BaseProc* proc = nullptr;
};
KSYS_CHECK_SIZE_NX150(CallArg, 0x50);

// Name from the CSV (evt::BaseProcLinkForEvent::ctor 0x7100dbda00, init, ctorWithEvtAndActor,
// ctorWithCallArg, assign, acquireActor). Vtable 0x7102423298 (destructors only; the inline
// destructor is emitted at 0x710059a430 / 0x710059a87c).
class BaseProcLinkForEvent {
public:
    BaseProcLinkForEvent();
    BaseProcLinkForEvent(const Metadata* metadata, act::BaseProc* proc);
    explicit BaseProcLinkForEvent(const CallArg& arg);
    virtual ~BaseProcLinkForEvent() = default;

    void init(const CallArg& arg);
    // 0x7100dbdda0: re-initialises this link from `other`'s parameters and actor.
    void assign(const BaseProcLinkForEvent& other);
    // 0x7100dbe080 (CSV evt::ResidentEvent::initWithEvent): init with `metadata` and `proc`.
    void initWithEvent(act::BaseProc* proc, const Metadata* metadata);
    act::Actor* acquireActor() const;
    // 0x7100dbe010
    void reset();

    /* 0x008 */ bool _8;
    /* 0x010 */ act::BaseProcLink mLink;
    /* 0x020 */ Metadata mMetadata;
    /* 0x178 */ bool _178;
    /* 0x179 */ bool _179;
    /* 0x180 */ void* _180;
    /* 0x188 */ bool _188;
    /* 0x18c */ sead::Matrix34f _18c;
    /* 0x1bc */ bool _1bc;
};
KSYS_CHECK_SIZE_NX150(BaseProcLinkForEvent, 0x1c0);

}  // namespace ksys::evt
