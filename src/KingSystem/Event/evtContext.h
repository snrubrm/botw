#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

class ActorBase;

// The event manager's event context (CSV evt::Context; EventMgr + 0x1d2b8 is the active one): the event
// flows that make up a running event (the main flow and the flows it starts) and a stack of indices of the
// flow that is currently running. Only the members used so far are declared.
class Context {
public:
    virtual ~Context();

    // 0x7100db9e2c (CSV evt::Context::setActorBeingDeleted)
    void setActorBeingDeleted();
    // 0x7100db9df4 (CSV evt::Context::setFlag4)
    void setFlag4();
    // 0x7100db9dbc (CSV evt::Context::updateEventsStatus)
    void updateEventsStatus();
    // 0x7100dba314 / 0x7100dba360 (CSV evt::Context::getEventName / getEntryPointName)
    sead::SafeString getEventName() const;
    sead::SafeString getEntryPointName() const;
    // 0x7100db9e38 (CSV evt::Context::getActorByPointer)
    ActorBase* getActorByPointer(act::BaseProc* proc);
    // 0x7100db9e64 (CSV evt::Context::getActorByName)
    ActorBase* getActorByName(const sead::SafeString& name, const sead::SafeString& entry);
    // 0x7100dba2e4 (CSV evt::Context::setNoDeleteCurrentActor)
    void setNoDeleteCurrentActor(bool no_delete);
    // 0x7100db9b40 (CSV evt::Context::x): forwards to EventFlow::x of the current flow and sets `_1f4`.
    void x(bool set);

    // inline-only in the original; names are guesses: the flows are read through the index stack both with
    // (PtrArray::at: null if out of range) and without a range check (PtrArray::operator()).
    EventFlow* getCurrentFlow() const { return mFlows.at(mFlowStack[mStackTop]); }
    EventFlow* getCurrentFlowUnchecked() const { return mFlows(mFlowStack[mStackTop]); }

private:
    /* 0x08 */ sead::PtrArray<EventFlow> mFlows;
    u8 _18[0x1e8 - 0x18];
    /* 0x1e8 */ sead::SafeArray<s8, 8> mFlowStack;
    /* 0x1f0 */ s32 mStackTop;
    /* 0x1f4 */ u8 _1f4;
    u8 _1f5[0x1f9 - 0x1f5];
    /* 0x1f9 */ bool mActorBeingDeleted;
    u8 _1fa[0x250 - 0x1fa];
};

}  // namespace ksys::evt
