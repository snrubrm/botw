#pragma once

#include <evfl/Flowchart.h>
#include <evfl/TimelineObj.h>
#include <heap/seadHeap.h>
#include <container/seadPtrArray.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

class EventResource;
class ActorBindings;
class EventFlow;
class ActorBase;
class Actor;

// The per-event actor set (CSV evt::S6) at EventFlowBase + 0x110.
class EventActorSet {
public:
    virtual ~EventActorSet();

    // 0x7100da283c (CSV evt::S6::callActorStuff): calls ActorBase::m8 of every actor
    void callActorStuff();
    // 0x7100da28e8 (CSV evt::S6::playActors)
    void playActors();
    // 0x7100da2c18 (CSV evt::S6::getActorByPointer): the actor whose proc link refers to `proc`
    ActorBase* getActorByPointer(act::BaseProc* proc) const;
    // 0x7100da2c94 (CSV evt::S6::getActorByName; not decompiled)
    ActorBase* getActorByName(const sead::SafeString& name, const sead::SafeString& entry) const;
    // 0x7100da2e84 (CSV unnamed): same body as getActorByPointer (non-const copy; placeholder name)
    ActorBase* sub_7100DA2E84(act::BaseProc* proc);
    // 0x7100da23c4 (CSV evt::S6::ctor)
    explicit EventActorSet(EventFlowBase* flow);
    // 0x7100da2408 (CSV evt::S6::allocActors; not decompiled)
    void allocActors(ActorBindings* bindings, sead::Heap* heap, EventFlow* slot);
    // 0x7100da2618 (CSV unnamed; not decompiled)
    bool sub_7100DA2618(ActorBindings* bindings);
    // 0x7100da2774 / 0x7100da375c (CSV evt::S6::x_3 / x_2; not decompiled)
    bool x_3(bool a1, bool a2);
    void x_2();
    // 0x7100da3624 (CSV evt::S6::x_4): whether every actor's x_0 is true
    bool x_4();
    // 0x7100da288c / 0x7100da3878 (CSV evt::S6::x_1 / x_0)
    void x_1();
    void x_0();
    // 0x7100da2700 (CSV unnamed; placeholder name): calls every actor's slot 5 and sets the state to 2
    void sub_7100DA2700(bool a1, bool a2);

    /* 0x08 */ sead::PtrArray<Actor> mActors;
    /* 0x18 */ s32 _18;
    u8 _1c[0x20 - 0x1c];
    /* 0x20 */ EventFlowBase* mFlow;
    /* 0x28 */ EventResource* mResource;
    /* 0x30 */ bool mNoDeleteCurrentActor;
    u8 _31[0x38 - 0x31];
    /* 0x38 */ void* _38;
    /* 0x40 */ s32 _40;  // number of actors that were initialised by sub_7100DA2618
    /* 0x44 */ s32 _44;
    /* 0x48 */ sead::Vector2f _48;
    /* 0x50 */ sead::Vector2f _50;
    u8 _58[0x58 - 0x58];
};

// Unknown object at EventFlowBase + 0x100 (polymorphic; slot 10 = isPlaying-like query).
class EventFlowHandle {
public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual bool m5() = 0;  // updates the flow (EventFlowBase::calc)
    virtual void m6() = 0;
    virtual const char* m7() = 0;
    virtual void m8(void* a1, void* a2) = 0;
    virtual void m9() = 0;
    virtual bool isPlaying() = 0;  // slot 10
};

// Unknown object at EventFlowBase + 0x118 (embeds the base proc link of the event's actor at +0x18).
struct EventFlowActorInfo {
    u8 _0[0x18];
    act::BaseProcLink mLink;
    // A second link (read by EventFlowBase::acquireEventFlow)
    act::BaseProcLink mLink2;
};

// The value of EventFlowBase::mType (names from the CSV function evt::EventFlowBase::isEventTypeNotMovieWithNoPath; the
// other enumerators are guesses).
SEAD_ENUM(EventFlowType, Flowchart, Timeline, Movie, MovieWithNoPath)

// 0x7100db6900 (CSV evt::getCurrentEventForReport; not decompiled): "<event name>"-style text of the flow that is
// being processed (sUnk_7102601530 / sUnk_7102601528), for the play reports.
const char* getCurrentEventForReport();

// 0x7102601528 (placeholder name): the flow whose handle is being updated (set by EventFlowBase::calc / the
// constructor; read by the event status reporting, CSV evt::getCurrentEventForReport).
class EventFlowBase;
extern EventFlowBase* sUnk_7102601528;

// An event flow instance (CSV: evt::EventFlowBase, the base of EventFlowFlowchart / EventFlowMovie /
// EventFlowTimeline; the CSV's `evt::EventFlow` is the EventFlowMgr slot class, see evtEventFlowMgr.h). Abstract.
// Only the members used so far are declared; the vtable has 18 slots (0-17).
class EventFlowBase {
public:
    virtual ~EventFlowBase();
    SEAD_RTTI_BASE(EventFlowBase)

    enum class Flag : u64 {
        _100000000 = 0x100000000,  // read by PlayerEventStartWait::leave_
        _80000000000 = 0x80000000000,
    };
    bool hasFlag(Flag flag) const { return (_340 & u64(flag)) != 0; }

    virtual void m4();  // empty
    // slot 5
    virtual f32 getFrameCount() const = 0;
    virtual s32 getEventFlowType() const = 0;  // 0 = flowchart, 1 = timeline, 2 / 3 = movie
    virtual void* m7();                        // returns nullptr
    virtual void m8();                         // empty
    virtual void printStatus(sead::BufferedSafeString* out);
    virtual s32 m10();  // returns 0 (EventFlowTimeline overrides it with an argument)
    virtual void m11() = 0;
    virtual void m12() = 0;
    virtual void m13() = 0;  // start
    virtual bool m14() = 0;  // update
    virtual void m15() = 0;
    virtual void m16() = 0;
    virtual void m17() = 0;

    // 0x7100db627c (CSV evt::EventFlowBase::getBaseProcLink)
    act::BaseProcLink* getBaseProcLink();
    // 0x7100db6288 (CSV evt::EventFlowBase::byte3FlagIsSet)
    bool byte3FlagIsSet() const;
    // 0x7100db8b84 (CSV evt::EventFlowBase::x): sets / clears the flag bits 0x80 + 0x20 and notifies the resource.
    void x(bool set);
    // 0x7100db7888 (CSV evt::EventFlowBase::setFlag4)
    void setFlag4();
    // 0x7100db8b68 (CSV evt::EventFlowBase::exitEventMaybe)
    void exitEventMaybe();
    // 0x7100db8a24 (CSV evt::EventFlowBase::isPlaying)
    bool isPlaying();
    // 0x7100db6cfc (CSV unnamed; called by Context::updateEventsStatus): forwards to the handle's slot 6
    void sub_7100DB6CFC();
    // 0x7100db6ad0 (CSV evt::EventFlowBase::calc): updates the handle with this flow registered as the current one
    bool calc();
    // 0x7100db6b1c (CSV evt::EventFlowBase::acquireEventFlow): takes a slot of the event flow manager that already
    // holds the resource (or initialises the resource), then lets the actor know about the flow
    void acquireEventFlow();
    // 0x7100db67ec (CSV evt::EventFlowBase::initEventAndReport)
    void initEventAndReport(bool a1);
    // 0x7100db7148 / 0x7100db718c (CSV evt::EventFlowBase::setupActors / initActors)
    void setupActors();
    void initActors();
    // 0x7100db7540 (CSV evt::EventFlowBase::x_0): releases the actor set and the resource once the actors are ready
    bool x_0(bool a1, bool a2);
    // 0x7100db8abc / 0x7100db8994 (CSV evt::EventFlowBase::x_7 / x_5)
    void x_7();
    void x_5(EventFlowBase* other);
    // inline-only in the original; name is a guess (the by-value copy gives the volatile SEAD_ENUM stack round trip
    // seen in isEventTypeNotMovieWithNoPath / x_3 / acquireEventFlow)
    EventFlowType getType() const { return mType; }
    // 0x7100db67c0 (CSV evt::EventFlowBase::isEventTypeNotMovieWithNoPath)
    bool isEventTypeNotMovieWithNoPath() const;
    // 0x7100db6c64 (CSV evt::EventFlowBase::x_3)
    bool x_3() const;
    // 0x7100db8b04 (CSV evt::EventFlowBase::x_4)
    bool x_4() const;
    // 0x7100db6c94 (CSV evt::EventFlowBase::x_1): 0 = not ready, 1 = loaded, 2 = loaded without extra model resources
    s32 x_1();
    // 0x7100db7a1c (CSV evt::EventFlowBase::x_8, 3.6 KB; not decompiled): return type unknown
    void x_8();
    // 0x7100db8bb8 (CSV unnamed; not decompiled)
    bool sub_7100DB8BB8(bool a1);

    /* 0x08 */ sead::Heap* mHeap;
    // The flow's data (passed to EventResource::init*) starts here
    /* 0x10 */ sead::FixedSafeString<64> mEventName;
    /* 0x68 */ sead::FixedSafeString<128> mEntryPointName;
    /* 0x100 */ EventFlowHandle* _100;
    /* 0x108 */ EventResource* _108;
    /* 0x110 */ EventActorSet* _110;
    /* 0x118 */ EventFlowActorInfo* _118;
    u8 _120[0x208 - 0x120];
    /* 0x208 */ EventFlowType mType;
    /* 0x20c */ f32 _20c;
    /* 0x210 */ EventFlow* mSlot;
    u8 _218[0x2c8 - 0x218];
    /* 0x2c8 */ s32 _2c8;
    u8 _2cc[0x2e8 - 0x2cc];
    u8 _2e8[0x340 - 0x2e8];  // a res::Handle at 0x2e8
    union {
        /* 0x340 */ u64 _340;
        u8 _340_bytes[8];
    };
    u8 _348[0x620 - 0x348];
};

class EventFlowFlowchart : public EventFlowBase {
public:
    ~EventFlowFlowchart() override;
    SEAD_RTTI_OVERRIDE(EventFlowFlowchart, EventFlowBase)

    f32 getFrameCount() const override;
    s32 getEventFlowType() const override;
    void m12() override;
    bool m14() override;
    void m15() override;
    void m16() override;
    void m17() override;

    /* 0x620 */ evfl::FlowchartContext mContext;
    /* 0x6b0 */ s32 _6b0;
    /* 0x6b4 */ f32 _6b4;
};
KSYS_CHECK_SIZE_NX150(EventFlowFlowchart, 0x6b8);

class EventFlowTimeline : public EventFlowBase {
public:
    ~EventFlowTimeline() override;
    SEAD_RTTI_OVERRIDE(EventFlowTimeline, EventFlowBase)

    f32 getFrameCount() const override;
    s32 getEventFlowType() const override;
    void* m7() override;
    void m13() override;
    bool m14() override;
    void m15() override;
    void m16() override;
    void m17() override;

    /* 0x620 */ s32 _620;
    u8 _624[4];
    /* 0x628 */ evfl::TimelineObj* _628;
    /* 0x630 */ s32 _630;
    u8 _634[0x638 - 0x634];
    /* 0x638 */ void* _638;
};

class EventFlowMovie : public EventFlowBase {
public:
    ~EventFlowMovie() override;
    SEAD_RTTI_OVERRIDE(EventFlowMovie, EventFlowBase)

    s32 getEventFlowType() const override;
    void printStatus(sead::BufferedSafeString* out) override;
    void m11() override;
    void m15() override;
    void m16() override;
    void m17() override;

    u8 _620[0x628 - 0x620];
    /* 0x628 */ const char* mMoviePath;
};

}  // namespace ksys::evt
