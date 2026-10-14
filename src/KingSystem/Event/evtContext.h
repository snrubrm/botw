#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

class ActorBase;
class EventFlow;

// The object at Context + 0x200 (placeholder; only its deleting destructor (slot 1) is used)
class ContextUnk200 {
public:
    virtual ~ContextUnk200();
};

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
    // 0x7100dba274 (CSV unnamed): sets flag bit 0x1000000000 on every flow
    void sub_7100DBA274();
    // 0x7100dba2ac (CSV unnamed): forwards `proc` to EventFlowBase::x_8 of the current flow
    bool sub_7100DBA2AC(act::BaseProc* proc);
    // 0x7100dba3ac (CSV unnamed): ANDs EventFlowBase::sub_7100DB8BB8(a1) over all flows
    bool sub_7100DBA3AC(bool a1);
    // 0x7100db9e38 (CSV evt::Context::getActorByPointer)
    ActorBase* getActorByPointer(act::BaseProc* proc);
    // 0x7100db9e64 (CSV evt::Context::getActorByName)
    ActorBase* getActorByName(const sead::SafeString& name, const sead::SafeString& entry);
    // 0x7100dba2e4 (CSV evt::Context::setNoDeleteCurrentActor)
    void setNoDeleteCurrentActor(bool no_delete);
    // 0x7100db9b40 (CSV evt::Context::x): forwards to EventFlowBase::x of the current flow and sets `_1f4`.
    void x(bool set);

    // inline-only in the original; names are guesses: the flows are read through the index stack both with
    // (PtrArray::at: null if out of range) and without a range check (PtrArray::operator()).
    EventFlowBase* getCurrentFlow() const { return mFlows.at(mFlowStack[mStackTop]); }
    EventFlowBase* getCurrentFlowUnchecked() const { return mFlows(mFlowStack[mStackTop]); }

private:
    // An entry of _240 (the child flows; made by the constructor)
    struct ChildFlow {
        EventFlow* flow;
        bool _8;
    };

    /* 0x08 */ sead::PtrArray<EventFlowBase> mFlows;

public:
    // _28 / _38 of this object: the actor link and the event metadata (the event name is compared by
    // Manager::isActiveEventNameEqualTo, the entry point is copied by Manager::getEventEntryPointName)
    /* 0x18 */ BaseProcLinkForEvent mProcLink;

private:
    /* 0x1d8 */ s32 _1d8;
    /* 0x1e0 */ sead::Heap* mHeap;
    /* 0x1e8 */ sead::SafeArray<s8, 8> mFlowStack;
    /* 0x1f0 */ s32 mStackTop;
    /* 0x1f4 */ u8 _1f4;
    u8 _1f5[0x1f7 - 0x1f5];
    /* 0x1f7 */ bool _1f7;  // set by the constructor when the metadata's _160 < 500 (also sets ActorSystem::_13b bit 0)
    u8 _1f8;
    /* 0x1f9 */ bool mActorBeingDeleted;
    u8 _1fa[0x200 - 0x1fa];
    // made by the constructor through Manager::_1d2c8 (slot 0); type unknown
    /* 0x200 */ ContextUnk200* _200;
    u8 _208[0x240 - 0x208];
    /* 0x240 */ sead::Buffer<ChildFlow> mChildFlows;
};

}  // namespace ksys::evt
