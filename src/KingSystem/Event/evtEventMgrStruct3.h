#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace al {
class ByamlIter;
}

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class EventFlow;
class EventFlowBase;
class EventMgrStruct3B;

// The event's actor ownership record. Native 127961C selects one of 200 0x58-byte
// records, binds mLink, adds a flow/data pair, and stores the record in Actor +0x1a0.
// Native 12793EC releases the actor and clears the owner pointers and active flag.
class EventActorLink {
public:
    // 0x71012793ec: release the actor, optionally notifying it before resetting the link.
    void releaseActor(act::Actor* actor, bool notify);
    // 0x710127950c: remove a flow owner, releasing the actor when none remain.
    void removeOwner(EventFlowBase* flow);

    act::BaseProcLink mLink;
    /* 0x10 */ bool mActive = false;
    struct Owner {
        EventFlowBase* flow = nullptr;
        void* data;  // initialized only when a flow owner is added by 127961C
    };
    /* 0x18 */ sead::SafeArray<Owner, 4> mOwners;

private:
    friend class EventActorLinkPool;
    // Producer operation in 127961C / 1279784; kept inline with its pool callers.
    void bindActor(act::Actor* actor, EventFlowBase* flow, void* data);
};
static_assert(sizeof(EventActorLink) == 0x58);

// Manager::init (DB1D10) allocates 0x44c0 bytes at +1d2e8 and initializes
// 200 actor ownership records. Release paths 127995C / 1279978 consume that pool.
class EventActorLinkPool {
public:
    void bindActor(act::Actor* actor, EventFlowBase* flow, void* data);
    void copyOwners(act::Actor* actor, const EventActorLink* source);
    void releaseActor(act::Actor* actor);
    void removeOwner(EventFlowBase* flow);

    sead::SafeArray<EventActorLink, 200> mLinks;
};
static_assert(sizeof(EventActorLinkPool) == 0x44c0);



// Native EventFlowMgr constructor owns two arrays of 0x18-byte entries (DBE0AC).
class EventMgrStruct3A {
public:
    EventMgrStruct3A();
    ~EventMgrStruct3A();
    void assignToActor(act::Actor* actor);
    // 0x7101279a54: AIScheduleUser plus NPC and unique-name suffixes for event binding.
    void formatActorName(sead::BufferedSafeString* name) const;
    // 127A008 sets/clears the shared flow-record association in the native schedule callers.
    void setFlowRecord(EventMgrStruct3B* record);
    // 0x7101279ffc (placeholder name; declared only): clears mFlowRecord and mAssigned
    void sub_7101279FFC();

    /* 0x00 */ act::Actor* mActor = nullptr;
    /* 0x08 */ EventMgrStruct3B* mFlowRecord = nullptr;
    /* 0x10 */ bool mAssigned = false;
    /* 0x11 */ bool mHasUniqueName = false;
};
static_assert(sizeof(EventMgrStruct3A) == 0x18);

// Native DC12A4 initializes the 0x190-byte records owned by EventFlowMgr.
class EventMgrStruct3B {
public:
    EventMgrStruct3B();

    // 0x7100dc1340 (placeholder name): sets the name, clears the flow list and stores the two values
    void sub_7100DC1340(s32 a1, s32 a2, const sead::SafeString& name);
    // 0x7100dc1448 (placeholder name): unloads the flows (with `force`, all of them; else those whose _120 is
    // clear) and resets the record
    void sub_7100DC1448(bool force);
    // 0x7100dc22e0 (placeholder name): drops a reference; the last one unloads all flows and resets the record.
    // `actor` is unused (callers pass the slot's actor or nullptr).
    void sub_7100DC22E0(act::Actor* actor);
    // 0x7100dc14f0: load the first actor's default/conditional schedule timelines, then retain.
    void loadBaischeduleStuff(EventMgrStruct3A* entry);
    // Load the quest actor timelines / map-tag event flows, retaining the owning record.
    void sub_7100DC1E64();
    void sub_7100DC2090(act::Actor* actor);
    // 0x7100dc1680: consumes a timeline entry, actor and optional unique-name selector.
    void loadAIScheduleTimelineInfo(const al::ByamlIter& timeline, act::Actor* actor,
                                    const char* unique_name);

    /* 0x000 */ sead::FixedSafeString<64> _0;
    /* 0x058 */ s32 _58 = 0;  // reference count
    u8 _5c[0x60 - 0x5c];
    /* 0x060 */ sead::SafeArray<EventFlow*, 32> _60;
    /* 0x160 */ s32 _160 = 0;
    /* 0x164 */ s32 _164 = 3;
    /* 0x168 */ s32 _168 = 0;
    /* 0x170 */ act::Actor* _170 = nullptr;
    // Native DBFE98 stores the distance to this record's actor.
    /* 0x178 */ f32 _178 = 0;
    /* 0x17c */ sead::Vector2f _17c = sead::Vector2f::zero;
    /* 0x184 */ sead::Vector2f _184 = sead::Vector2f::zero;
};
static_assert(sizeof(EventMgrStruct3B) == 0x190);

}  // namespace ksys::evt
