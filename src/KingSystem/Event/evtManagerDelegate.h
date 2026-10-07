#pragma once

#include <heap/seadHeap.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtEventFlow.h"

namespace evfl {
struct ResAction;
struct ResQuery;
}  // namespace evfl

namespace ksys::evt {

class Action;
class ActorBase;
class ActorBinding;
class EventActorSet;
class Query;
class S5;

// The creation arguments of an event flow (EventFlowBase::ctor 0x7100db58b8; only the members used so far).
struct EventFlowCreateArg {
    /* 0x00 */ sead::Heap* heap;
    /* 0x08 */ EventFlowActorInfo* info;
    u8 _10[0x20 - 0x10];
    /* 0x20 */ s32 _20;
    u8 _24[4];
    /* 0x28 */ const void* _28;
    u8 _30[0x38 - 0x30];
    /* 0x38 */ bool _38;
    /* 0x39 */ bool _39;
    /* 0x3a */ bool _3a;
    /* 0x3b */ bool _3b;
};

// The delegate of the event manager (Manager + 0x1d2c8; the game's implementation is uking::EventDelegate, CSV
// ukingEventMgr, vtable 0x710246ca38 without RTTI). It creates the event system's polymorphic parts and answers the
// game-specific questions of the event system.
class ManagerDelegate {
public:
    virtual S5* makeS5(sead::Heap* heap) = 0;
    virtual EventFlowHandle* makeS7(const EventFlowCreateArg* arg, EventFlowBase* flow) = 0;
    virtual Actor* makeActor(ActorBinding* binding, EventActorSet* set, sead::Heap* heap) = 0;
    virtual Action* makeAction(const evfl::ResAction* res, ActorBase* actor, sead::Heap* heap) = 0;
    virtual Query* makeQuery(const evfl::ResQuery* res, ActorBase* actor, sead::Heap* heap) = 0;
    virtual bool canStartEventEvenInAir(const BaseProcLinkForEvent& link) = 0;
    virtual bool m6(sead::Matrix34f* out, const sead::SafeString& stage, const sead::SafeString& pos_name) = 0;
    virtual void m7() = 0;
    virtual void m8(s32 value, s32 count) = 0;
};

}  // namespace ksys::evt
