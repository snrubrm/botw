#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

class EventResource;
class EventFlow;

// A slot of the EventFlowMgr's table (0x148 bytes). The CSV calls this class `evt::EventFlow` (ctor 0x7100dc00e8,
// init, x, x_0, unload, loadEventResource, ...; EventFlowMgr::unload / loadSimple take / return it) while the flow
// instance class (CSV evt::EventFlowBase) is `ksys::evt::EventFlow` in this tree. Renamed to avoid the clash.
class EventFlowSlot {
public:
    // 0x7100dc1060 / 0x7100dc106c (CSV EventFlow::setState4 / setState3)
    void setState4();
    void setState3();
    // 0x7100dc1258 (CSV EventFlow::loadEventResource): true if there is no resource
    bool loadEventResource(bool a1);
    // 0x7100dc1078 (CSV EventFlow::unload; not decompiled)
    void unload(bool a1);

    /* 0x00 */ EventResource* mResource;
    /* 0x08 */ s32 mState;  // 0: free; 3: ?
    /* 0x0c */ s32 _c;
    u8 _10[0x148 - 0x10];
};
static_assert(sizeof(EventFlowSlot) == 0x148);

// Name from the CSV (EventFlowMgr::ctor 0x7100dbe0ac, load, loadSimple, unload, ...). Only what is
// used so far is declared.
class EventFlowMgr {
public:
    // 0x7100dbeb4c, 0x7100dbf048: these really return / take an EventFlowSlot (the CSV's `evt::EventFlow`), but the
    // callers (ResidentEvent, DeadlyBlowWeaponRoot::_f8 / _100) use the flow instance type `EventFlow` for the pointer,
    // so they stay declared with it until the two classes are renamed (not decompiled for that reason).
    EventFlow* loadSimple(const sead::SafeString& event_name, const sead::SafeString& entry_point);
    void unload(EventFlow* flow);
    // 0x7100dbf588 (CSV EventFlowMgr::areAllEventFlowsReady)
    bool areAllEventFlowsReady() const;
    // 0x7100dc0024 (CSV EventFlowMgr::loadEventResourceForAllEventFlows)
    bool loadEventResourceForAllEventFlows(bool a1);

private:
    u8 _0[8];
    /* 0x08 */ sead::Buffer<EventFlowSlot> mSlots;
    u8 _18[0x78 - 0x18];
    /* 0x78 */ sead::CriticalSection mCS;
};

}  // namespace ksys::evt
