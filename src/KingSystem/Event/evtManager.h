#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace ksys {
class OverlayArenaSystemS1;
struct MesTransceiverId;
}

namespace ksys::act {
class Actor;
}

namespace ksys {
class Message;
struct MesTransceiverId;
enum MessageType : u32;
}

namespace ksys::evt {

class ActorFactory;
class BaseProcLinkForEvent;
class Context;
class EventFlow;
class EventFlowBase;
class EventDebugA;
class EventDebugB;
class EventXlinkInfo;
class EventMgrStruct1;
struct CallArg;
class Metadata;

// 0x7101277154 (CSV evt::initDebugStuff; placeholder name and parameter type: the object at Manager + 0x1d110)
void sub_7101277154(EventDebugA* debug);
// 0x7100dadcd0 (CSV unnamed; placeholder name and parameter type: the object at Manager + 0x1d120)
void sub_7100DADCD0(EventDebugB* debug);

// The object at evt::Manager + 0x1d108 (placeholder class; only slot 21 is known: whether an event may start in the air).
class StartableAirChecker {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual bool m21();
};

// TODO
// CSV EventSysActors (Manager + 0x1d378's object; declared only).
class EventSysActors {
public:
    // 0x7100dc7c84 (CSV EventSysActors::finishedLoading)
    bool finishedLoading();
};

class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void init(sead::Heap* heap);

    EventFlowBase* getActiveEvent() const;
    // 0x7100db222c (CSV EventMgr::__auto7): same body as getActiveEvent() const (placeholder name)
    EventFlowBase* sub_7100DB222C();
    // 0x7100db2440 (CSV EventMgr::checkEventCancel): flag bit 0x2000 of the active flow
    bool checkEventCancel() const;
    // 0x7100db2480 (name is a guess; lane4 s45): bit 7 of byte 5 of the active flow's flags (_340_bytes).
    bool checkJustBeforeEventCancel() const;
    bool hasActiveEvent() const;
    // 0x7100db2b1c (CSV EventMgr::someWeirdHardcodedCheck_KorokOrGanonOrBowling; declared only; lane4 s31):
    // Actor::onJobPush1_ sets / clears ActorFlag 0x3f with the result.
    bool someWeirdHardcodedCheck_KorokOrGanonOrBowling(act::Actor* actor);

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
    // inline-only in the original; name is a guess
    ActorFactory* getActorFactory() const { return _1d2c8; }

    void setNoDeleteCurrentActor(bool no_delete);

    // 0x7100db07c4 (CSV EventMgr::doCallEvent; not decompiled): `*out_result` is 500 when the event was only queued (?)
    bool doCallEvent(const CallArg& arg, s32* out_result);

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
    // 0x7100db1184: the name of the active event (an empty string without one)
    const char* sub_7100DB1184() const;

    // 0x7100db20d0 / 0x7100db137c (CSV EventMgr::__auto11 / __auto8; placeholder names): the active flow's
    // type is 1 (timeline) / the `_1b8` member of the active flow's resource
    bool sub_7100DB20D0() const;
    EventXlinkInfo* sub_7100DB137C() const;
    // 0x7100db2804 / 0x7100db2884 (CSV EventMgr::__auto0 / __auto13; placeholder names)
    bool sub_7100DB2804(bool a1);
    // 0x7100db26d0 (CSV EventMgr::finishedLoadingResidentData)
    bool finishedLoadingResidentData();
    // 0x7100db2744 (CSV EventMgr::eventResidentMgrFinished)
    bool eventResidentMgrFinished();
    void sub_7100DB2884();

    // 0x7100db19dc (CSV EventMgr::__auto4, placeholder name; lane4 s23): `_1d2c0 != nullptr ||
    // _1d170 < 1`, i.e. no event is playing / being set up (GanonBeast "rain" update).
    bool sub_7100DB19DC() const;
    // 0x7100db19c0 (CSV unnamed; placeholder name): decrements the alive event flow count (not below 0)
    void sub_7100DB19C0();
    // 0x7100db101c (CSV EventMgr::getActiveEventName): the names of the active context's current flow (either
    // output may be null); false if there is no active context
    bool getActiveEventName(const char** event_name, const char** entry_point_name) const;
    // 0x7100db2278 (CSV EventMgr::getBaseProcLinkFromActiveEvent): the link of the active event's actor `name`
    act::BaseProcLink* getBaseProcLinkFromActiveEvent(const sead::SafeString& name,
                                                      const sead::SafeString& entry_point) const;
    // 0x7100db12d8 (CSV EventMgr::getBaseProcLinkForActorOrActiveLink): the link of the context that has an event
    // actor for `proc` (the active context's link if none has / `proc` is null)
    act::BaseProcLink* getBaseProcLinkForActorOrActiveLink(act::BaseProc* proc) const;
    // 0x7100db0ea0 (CSV EventMgr::callEvent_0): message handler: calls the event described by the
    // BaseProcLinkForEvent in the user data of the message types 0x800001 / 0x800002
    bool sub_7100DB0EA0(const Message* message);
    // 0x7100db0fb0 (CSV EventMgr::__auto14; declared only): sends `type` with `user_data` to `dest` through the
    // manager's message transceiver (at +0x38; on the processing thread if called from it)
    bool sub_7100DB0FB0(const MesTransceiverId& dest, MessageType type, void* user_data);
    // 0x7100db05f4 (CSV EventMgr::isEventStartableAir): true unless the event's info entry says "is_startable_air" is
    // false and the (unknown) checker object at +0x1d108 reports that the player is not in the air
    bool isEventStartableAir(const BaseProcLinkForEvent& link);
    // 0x7100db06ec (CSV EventMgr::isEventStartableAir_0; placeholder name): the "is_startable_air" key of the event's
    // info entry (false if there is none or the check is skipped)
    bool sub_7100DB06EC(const BaseProcLinkForEvent& link);
    // 0x7100db1f44 (CSV EventMgr::checkActiveContextEventName): like isActiveEventNameEqualTo, but the active context
    // is re-read for the second comparison
    bool checkActiveContextEventName(const sead::SafeString& event_name,
                                     const sead::SafeString& entry_point) const;
    // 0x7100db2a9c (CSV EventMgr::x_3; placeholder name; called by PlayerDead::calc_): whether the active event is
    // the one of the link's metadata
    bool sub_7100DB2A9C(const BaseProcLinkForEvent& link) const;
    // 0x7100daf80c (CSV EventMgr::patrolPreCalc): runs the debug objects at 0x1d110 / 0x1d120
    void patrolPreCalc();
    // 0x7100db2140 (CSV EventMgr::__auto3; placeholder name; called by Actor::onEnterCalc_): false without an active
    // event or while its flow's entry point is the bowling "RollResult_Npc_Bowling_StepStart", else the active
    // context's sub_7100DBA2AC(proc)
    bool sub_7100DB2140(act::BaseProc* proc);
    // 0x7100db3750 (CSV EventMgr::__auto16; placeholder name): unloads the two flows at 0x1d3e0 / 0x1d3e8
    void sub_7100DB3750();
    // 0x7100db37c0 (CSV EventMgr::setActorBeingDeletedOnContexts): for every context except the active one
    // that has `proc` as an event actor
    void setActorBeingDeletedOnContexts(act::BaseProc* proc);
    // 0x7100db235c (CSV EventMgr::getEventEntryPointName): copies the active context's string at 0xb8 to `out`
    bool getEventEntryPointName(sead::BufferedSafeString* out) const;
    // 0x7100db11d4 (CSV EventMgr::getStarterActor): the actor behind getBaseProcLinkForActorOrActiveLink(proc)
    act::Actor* getStarterActor(act::BaseProc* proc) const;
    // 0x7100db10b0 (CSV EventMgr::__auto10; placeholder name)
    bool sub_7100DB10B0(const void* a1, act::BaseProc* proc, void** out_1b8, void** out_1c0) const;
    // 0x7100db22a8 (CSV EventMgr::__auto5; placeholder name): the link of the active event's "Argument" actor
    // (else of its "Current" actor)
    act::BaseProcLink* sub_7100DB22A8() const;

private:
    friend class ksys::OverlayArenaSystemS1;

    u8 pad_28[0x38 - 0x28];

public:
    // The event manager actor's message transceiver (0x38 - 0x90; its id is read by SleepBedRoot::calc_ and
    // ResidentEvent::sendMessageToEventMgrActor as the destination of Actor::sendMessage).
    /* 0x38 */ ActorMessageTransceiver mTransceiver;

private:
    u8 pad_90[0x1d108 - 0x90];
    /* 0x1d108 */ StartableAirChecker* _1d108;
    /* 0x1d110 */ EventDebugA* _1d110;
    u8 pad_1d118[0x1d120 - 0x1d118];
    /* 0x1d120 */ EventDebugB* _1d120;
    u8 pad_1d128[0x1d170 - 0x1d128];
    /* 0x1d170 */ s32 mAliveEventFlowCount;
    u8 pad_1d174[0x1d180 - 0x1d174];
    sead::Heap* mEventHeap;
    u8 pad_1d188[0x1d1b0 - 0x1d188];
    /* 0x1d1b0 */ u32 _1d1b0;
    u8 pad_1d1b4[0x1d1b8 - 0x1d1b4];
    /* 0x1d1b8 */ Context* mContexts[32];

public:
    // Tested by uking::action::FireWood::calc_ (null: no event is running?).
    Context* _1d2b8;

private:
    /* 0x1d2c0 */ void* _1d2c0;
    /* 0x1d2c8 */ ActorFactory* _1d2c8;
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
    u8 pad_1d2fc[0x1d378 - 0x1d2fc];
    /* 0x1d378 */ EventSysActors* _1d378;
    u8 pad_1d380[0x1d3e0 - 0x1d380];
    /* 0x1d3e0 */ EventFlow* _1d3e0;
    /* 0x1d3e8 */ EventFlow* _1d3e8;
};

}  // namespace ksys::evt

// 0x7100dc86ac (CSV name): copies the names of the active event's flow / entry point for `actor` into
// `flow` / `entry` (either may be null).
void getActiveEventFlowPath_0(ksys::act::Actor* actor, sead::BufferedSafeString* flow,
                              sead::BufferedSafeString* entry);
// 0x7100dc8838 (CSV name): copies "<flow><entry>" of the active event for `actor` into `path`.
void getActiveEventFlowPath(ksys::act::Actor* actor, sead::BufferedSafeString* path);
