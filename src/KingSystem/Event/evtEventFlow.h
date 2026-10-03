#pragma once

#include <evfl/TimelineObj.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

class EventResource;

// Unknown object at EventFlow + 0x100 (polymorphic; slot 10 = isPlaying-like query).
class EventFlowHandle {
public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void m9() = 0;
    virtual bool isPlaying() = 0;  // slot 10
};

// Unknown object at EventFlow + 0x118 (embeds the base proc link of the event's actor at +0x18).
struct EventFlowActorInfo {
    u8 _0[0x18];
    act::BaseProcLink mLink;
};

// An event flow instance (CSV: evt::EventFlowBase, the base of EventFlowFlowchart / EventFlowMovie /
// EventFlowTimeline; EventFlowMgr::unload takes `EventFlow*`, which is the real class name). Abstract.
// Only the members used so far are declared; the vtable has 18 slots (0-17).
class EventFlow {
public:
    virtual ~EventFlow();
    SEAD_RTTI_BASE(EventFlow)

    virtual void m4();  // empty
    // slot 5
    virtual f32 getFrameCount() const = 0;
    virtual s32 getEventFlowType() const = 0;  // 0 = flowchart, 1 = timeline, 2 / 3 = movie
    virtual void* m7();                        // returns nullptr
    virtual void m8();                         // empty
    virtual void printStatus();
    virtual s32 m10();  // returns 0 (FlowFlowchart: isFinished; EventFlowTimeline: takes an argument)
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

    u8 _8[0x10 - 0x8];
    u8 _10[0x68 - 0x10];   // the flow's data (passed to EventResource::init*)
    u8 _68[0x100 - 0x68];
    /* 0x100 */ EventFlowHandle* _100;
    /* 0x108 */ EventResource* _108;
    /* 0x110 */ void* _110;
    /* 0x118 */ EventFlowActorInfo* _118;
    u8 _120[0x340 - 0x120];
    union {
        /* 0x340 */ u64 _340;
        u8 _340_bytes[8];
    };
    u8 _348[0x620 - 0x348];
};

class EventFlowFlowchart : public EventFlow {
public:
    ~EventFlowFlowchart() override;
    SEAD_RTTI_OVERRIDE(EventFlowFlowchart, EventFlow)

    f32 getFrameCount() const override;
    s32 getEventFlowType() const override;
    s32 m10() override;
    void m15() override;
    void m16() override;
    void m17() override;

    u8 _620[0x69c - 0x620];
    /* 0x69c */ s32 _69c;
    u8 _6a0[0x6b4 - 0x6a0];
    /* 0x6b4 */ f32 _6b4;
};

class EventFlowTimeline : public EventFlow {
public:
    ~EventFlowTimeline() override;
    SEAD_RTTI_OVERRIDE(EventFlowTimeline, EventFlow)

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

class EventFlowMovie : public EventFlow {
public:
    ~EventFlowMovie() override;
    SEAD_RTTI_OVERRIDE(EventFlowMovie, EventFlow)

    void m11() override;
    void m15() override;
    void m16() override;
    void m17() override;
};

}  // namespace ksys::evt
