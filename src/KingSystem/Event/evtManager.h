#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys {
class OverlayArenaSystemS1;
struct MesTransceiverId;
}

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class Event;
class EventFlow;
class EventMgrStruct1;
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

    // 0x7100db199c (CSV EventMgr::incrementAliveEventFlowCount): saturates at 256.
    void incrementAliveEventFlowCount();
    // 0x7100db272c (CSV EventMgr::setFlags1000)
    void setFlags1000();
    // 0x7100db24c0 (CSV EventMgr::initBeforeStageGen)
    void initBeforeStageGen();
    // 0x7100db04d8 (CSV EventMgr::initBeforeStageGenB)
    void initBeforeStageGenB();

    sead::Heap* getEventHeap() const { return mEventHeap; }

    bool callEvent(const Metadata& metadata, act::Actor* actor = nullptr, void* x = nullptr);
    // 0x7100db0c44 (CSV EventMgr::callEvent)
    bool callEvent(const CallArg& arg);

    EventFlowMgr* getEventFlowMgr() const { return mEventFlowMgr; }

    void setNoDeleteCurrentActor(bool no_delete);

    // 0x7100db0ca0: always false (placeholder name; AssassinMiddleAzitoRoot passes a Metadata and
    // its actor).
    bool sub_7100DB0CA0(const Metadata& metadata, act::Actor* actor);
    // 0x7100db2910 (CSV name): whether the active event is `event_name` / `entry_point`.
    bool isActiveEventNameEqualTo(const sead::SafeString& event_name,
                                  const sead::SafeString& entry_point) const;

    // 0x7100db1138 / 0x7100db1158 / 0x7100db1174: EventMgrStruct1 entry `idx` (-99: none): clock
    // time minus the entry's _0 / free the entry / the entry's _4.
    f32 sub_7100DB1138(int idx) const;
    void sub_7100DB1158(int idx);
    f32 sub_7100DB1174(int idx) const;

    // 0x7100db19dc (CSV EventMgr::__auto4, placeholder name; lane4 s23): `_1d2c0 != nullptr ||
    // _1d170 < 1`, i.e. no event is playing / being set up (GanonBeast "rain" update).
    bool sub_7100DB19DC() const;

private:
    friend class ksys::OverlayArenaSystemS1;

    u8 pad_28[0x48 - 0x28];

public:
    // The message transceiver id of the event manager actor (placeholder name; read by
    // SleepBedRoot::calc_ and ResidentEvent::sendMessageToEventMgrActor, which pass `*_48` as the
    // destination of Actor::sendMessage).
    /* 0x48 */ const MesTransceiverId* _48;

private:
    u8 pad_50[0x1d170 - 0x50];
    /* 0x1d170 */ s32 mAliveEventFlowCount;
    u8 pad_1d174[0x1d180 - 0x1d174];
    sead::Heap* mEventHeap;
    u8 pad_1d188[0x1d1b0 - 0x1d188];
    /* 0x1d1b0 */ u32 _1d1b0;
    u8 pad_1d1b4[0x1d2b8 - 0x1d1b4];

public:
    // Tested by uking::action::FireWood::calc_ (null: no event is running?).
    void* _1d2b8;

private:
    u8 pad_1d2c0[0x1d2d0 - 0x1d2c0];
    EventMgrStruct1* _1d2d0;
    u8 pad_1d2d8[0x1d2e0 - 0x1d2d8];
    EventFlowMgr* mEventFlowMgr;
    u8 pad_1d2e8[0x1d2f4 - 0x1d2e8];

public:
    // Flag word; bit 0 is cleared by uking::action::PlayerHellStartWait::leave_.
    union {
        u32 _1d2f4;
        u8 _1d2f4_bytes[4];
    };
    /* 0x1d2f8 */ s32 _1d2f8;
};

}  // namespace ksys::evt

// 0x7100dc86ac (CSV name): copies the names of the active event's flow / entry point for `actor` into
// `flow` / `entry` (either may be null).
void getActiveEventFlowPath_0(ksys::act::Actor* actor, sead::BufferedSafeString* flow,
                              sead::BufferedSafeString* entry);
// 0x7100dc8838 (CSV name): copies "<flow><entry>" of the active event for `actor` into `path`.
void getActiveEventFlowPath(ksys::act::Actor* actor, sead::BufferedSafeString* path);
