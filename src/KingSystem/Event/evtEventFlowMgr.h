#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtEventMgrStruct3.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

class EventResource;
class EventFlow;

// A slot of the EventFlowMgr's table (0x148 bytes; CSV `evt::EventFlow`: ctor 0x7100dc00e8, init, x, x_0, unload,
// loadEventResource, ...; EventFlowMgr::unload / loadSimple take / return it). The flow instance class (the base of
// EventFlowFlowchart / Timeline / Movie) is EventFlowBase (evtEventFlow.h).
class EventFlow {
public:
    // One entry of the flow's actor table (0x30 bytes; the first member is read by BaseProcLink::getProc).
    struct ActorEntry {
        act::BaseProcLink mLink;
        act::BaseProcHandle mHandle;
        /* 0x20 */ u64 mKey;
        u8 _28[0x30 - 0x28];
    };

    // 0x7100dc00e8
    EventFlow();

    // 0x7100dc1060 / 0x7100dc106c (CSV EventFlow::setState4 / setState3)
    void setState4();
    void setState3();
    // 0x7100dc1258 (CSV EventFlow::loadEventResource): true if there is no resource
    bool loadEventResource(bool a1);
    // 0x7100dc1160 (CSV unnamed): if the slot is in use: resets the actor links, frees the actor table and the
    // resource and marks the slot free
    void sub_7100DC1160();
    // 0x7100dc1078 (CSV EventFlow::unload; not decompiled)
    void unload(bool a1);
    // 0x7100dc01ec (CSV EventFlow::initAndAllocResource): copies the names, allocates the EventResource on `heap`
    void initAndAllocResource(sead::Heap* heap, const sead::SafeString& event_name,
                              const sead::SafeString& entry_point, const al::ByamlIter& info);
    // 0x7100dc040c (CSV EventFlow::init; not decompiled)
    void init(bool a1);
    // 0x7100dc0eec (CSV unnamed): true if the slot is free; for a used slot with a resource the init status is
    // formatted into a local buffer (the original discards it) and false is returned.
    bool sub_7100DC0EEC();

    /* 0x00 */ EventResource* mResource;
    /* 0x08 */ s32 mState;  // 0: free; 3: ?
    /* 0x0c */ s32 _c;
    /* 0x10 */ sead::FixedSafeString<64> mEventName;
    /* 0x68 */ sead::FixedSafeString<128> mEntryPointName;
    /* 0x100 */ sead::Heap* mHeap;
    /* 0x108 */ al::ByamlIter mInfoIter;
    /* 0x118 */ s32 _118;
    /* 0x11c */ s32 mRefCount;
    /* 0x120 */ bool _120;
    /* 0x128 */ sead::Buffer<ActorEntry> mActors;
    /* 0x138 */ sead::Vector2f _138;
    /* 0x140 */ sead::Vector2f _140;
};
static_assert(sizeof(EventFlow) == 0x148);

// 0x7102601530 (placeholder name): the flow that is being initialised (set by EventFlow::initAndAllocResource; read by
// the event status reporting, CSV evt::getCurrentEventForReport).
extern EventFlow* sUnk_7102601530;

// Name from the CSV (EventFlowMgr::ctor 0x7100dbe0ac, load, loadSimple, unload, ...). Only what is
// used so far is declared.
class EventFlowMgr {
public:
    // 0x7100dbe600; native vtable 0x71024de180 has only D1/D0.
    virtual ~EventFlowMgr();
    // 0x7100dbeb4c (CSV EventFlowMgr::loadSimple): forwards to load() with flags false and no extra argument
    EventFlow* loadSimple(const sead::SafeString& event_name, const sead::SafeString& entry_point);
    // 0x7100dbf048
    void unload(EventFlow* flow);
    // 0x7100dbeb5c (CSV EventFlowMgr::load; not decompiled)
    EventFlow* load(const sead::SafeString& event_name, const sead::SafeString& entry_point, bool a3, bool a4,
                    void* a5);
    // 0x7100dbf080 (CSV EventFlowMgr::acquireEventFlow; not decompiled)
    EventFlow* acquireEventFlow(const sead::SafeString& event_name, const sead::SafeString& entry_point);
    // 0x7100dbe73c (CSV EventFlowMgr::calc)
    void calc(bool a1);
    // 0x7100dbe85c (CSV EventFlowMgr::x_0): updates the actor, quest and map-tag records.
    void x_0();
    // The 64 actor slots are grouped by formatted schedule name and selected by planar distance.
    void x_3(u64* visited, const sead::Vector3f& position, const sead::SafeString& name,
             EventMgrStruct3A** farthest, f32* farthest_distance, EventMgrStruct3A* source);
    void sub_7100DBFBAC(f32 nearest_distance, f32 farthest_distance,
                        EventMgrStruct3A* nearest, EventMgrStruct3A* farthest);
    // Native DBFA00 / DBFE98 consume one actor binding / the player position.
    void x_4(EventMgrStruct3A* entry);
    // 0x7100dbf72c (CSV EventFlowMgr::x)
    void x(EventMgrStruct3A* entry);
    void x_5(const sead::Vector3f& position);
    // 0x7100dbf2b4 (CSV unnamed; declared only; placeholder name): with a1, EventFlow::sub_7100DC1160 on every slot,
    // else unloads the slots whose _120 is clear
    void sub_7100DBF2B4(bool a1);
    // 0x7100dbf50c (CSV unnamed): true if every slot is free or has finished its init
    bool sub_7100DBF50C();
    // 0x7100dbf588 (CSV EventFlowMgr::areAllEventFlowsReady)
    bool areAllEventFlowsReady() const;
    // 0x7100dc0024 (CSV EventFlowMgr::loadEventResourceForAllEventFlows)
    bool loadEventResourceForAllEventFlows(bool a1);

private:
    /* 0x08 */ sead::Buffer<EventFlow> mSlots;
    /* 0x18 */ sead::Heap* mHeap;
    /* 0x20 */ s32 mCalcCount;
    /* 0x28 */ sead::Buffer<EventMgrStruct3A> _28;
    /* 0x38 */ sead::Buffer<EventMgrStruct3A> _38;
    /* 0x48 */ sead::Buffer<EventMgrStruct3B> _48;
    /* 0x58 */ sead::Buffer<EventMgrStruct3B> _58;
    /* 0x68 */ sead::Buffer<EventMgrStruct3B> _68;
    /* 0x78 */ sead::CriticalSection mCS;
    /* 0xb8 */ bool _b8;
};

static_assert(sizeof(EventFlowMgr) == 0xc0);

}  // namespace ksys::evt
