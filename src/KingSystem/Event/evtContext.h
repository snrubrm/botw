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
    // 0x7100dba274 (CSV unnamed): sets flag bit 0x1000000000 on every flow
    void sub_7100DBA274();
    // 0x7100dba2ac (CSV unnamed): forwards to EventFlowBase::x_8 of the current flow
    void sub_7100DBA2AC();
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
    /* 0x08 */ sead::PtrArray<EventFlowBase> mFlows;
    u8 _18[0x28 - 0x18];
public:
    /* 0x28 */ act::BaseProcLink mLink;

private:
    u8 _38[0xb8 - 0x38];

public:
    /* 0xb8 */ sead::FixedSafeString<64> _b8;  // copied by Manager::getEventEntryPointName (size guessed)

private:
    u8 _110[0x1e8 - 0x110];
    /* 0x1e8 */ sead::SafeArray<s8, 8> mFlowStack;
    /* 0x1f0 */ s32 mStackTop;
    /* 0x1f4 */ u8 _1f4;
    u8 _1f5[0x1f9 - 0x1f5];
    /* 0x1f9 */ bool mActorBeingDeleted;
    u8 _1fa[0x250 - 0x1fa];
};

}  // namespace ksys::evt
