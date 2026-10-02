#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys {
class OverlayArenaSystemS1;
}

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class Event;
class EventFlow;
struct CallArg;
class Metadata;

// Name from the CSV (EventFlowMgr::ctor 0x7100dbe0ac, load, loadSimple, unload, ...). Only what is
// used so far is declared.
class EventFlowMgr {
public:
    // 0x7100dbeb4c
    EventFlow* loadSimple(const sead::SafeString& event_name, const sead::SafeString& entry_point);
    // 0x7100dbf048
    void unload(EventFlow* flow);
};

// TODO
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void init(sead::Heap* heap);

    Event* getActiveEvent() const;
    bool hasActiveEvent() const;

    sead::Heap* getEventHeap() const { return mEventHeap; }

    bool callEvent(const Metadata& metadata, act::Actor* actor = nullptr, void* x = nullptr);
    // 0x7100db0c44 (CSV EventMgr::callEvent)
    bool callEvent(const CallArg& arg);

    EventFlowMgr* getEventFlowMgr() const { return mEventFlowMgr; }

    void setNoDeleteCurrentActor(bool no_delete);

private:
    friend class ksys::OverlayArenaSystemS1;

    u8 pad_20[0x1d178 - 0x20];
    sead::Heap* mEventHeap;
    u8 pad_1d188[0x1d2b8 - 0x1d188];
    void* _1d2b8;
    u8 pad_1d2c0[0x1d2e0 - 0x1d2c0];
    EventFlowMgr* mEventFlowMgr;
    u8 pad_1d2e8[0x1d2f4 - 0x1d2e8];
    u32 _1d2f4;
};

}  // namespace ksys::evt
