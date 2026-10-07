#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

// The current speaker of the event system (EventSystem + 0xc0; CSV evt::S3, placeholder name).
class EventSpeaker {
public:
    // 0x7100e496ac (CSV evt::S3::ctor)
    EventSpeaker();
    // D1 0x71008aa750 (CSV evt::EventSystem::x_6), D0 0x71008ac2a0
    virtual ~EventSpeaker() = default;

    // 0x7100e497fc (CSV evt::S3::setSpeaker): replaces the speaker link; false if `actor` could not be linked.
    bool setSpeaker(act::Actor* actor);
    // 0x7100e497b8 (placeholder name; lane5 s5): whether `actor` is the linked speaker.
    bool sub_7100E497B8(act::Actor* actor) const;
    // 0x7100e498f0 / 0x7100e49944 (placeholder names): copy the previous / current position of the speaker actor
    // (false without a linked actor).
    bool getPreviousPos(sead::Vector3f* out) const;
    bool getPos(sead::Vector3f* out) const;

    /* 0x08 */ act::BaseProcLink mLink;
    /* 0x18 */ sead::Vector3f mPreviousPos;
    /* 0x24 */ sead::Vector3f mPos;
    /* 0x30 */ sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(EventSpeaker, 0x70);

// CSV evt::EventSystem (instance pointer 0x71025d0c50). A sead singleton (disposer at +0x10) and the message handler of
// its transceiver (the IHandler base at +0; vtable 0x710246c9c8: D1, D0, handleMessage / the thunks and the default
// handleAck). Only the members used so far are declared; createInstance (0x71008aa614) has the constructor inlined.
class EventSystem : public ActorMessageTransceiver::IHandler {
    SEAD_SINGLETON_DISPOSER(EventSystem)
    EventSystem();

public:
    // D1 0x71008aa6f4 (CSV x_5), D0 0x71008aa7e4, thunks 0x71008aa788 / 0x71008aa848
    ~EventSystem() override;
    // 0x71008abf28
    int handleMessage(const Message& message) override;

    // 0x71008abf48: speaker assignment.
    bool setSpeaker(act::Actor* actor);

    /* 0x30 */ u16 _30 = 0;
    /* 0x32 */ u8 _32 = 0;
    u8 _33;
    /* 0x34 */ u8 _34[8] = {};
    /* 0x3c */ bool _3c[18];
    u8 _4e[2];
    /* 0x50 */ s32 _50;
    u8 _54[4];
    /* 0x58 */ Unk_710246c4d8 _58;
    /* 0x68 */ ActorMessageTransceiver mTransceiver{*this};
    /* 0xc0 */ EventSpeaker mSpeaker;
    /* 0x130 */ u8 _130[0x16];
    u8 _146[2];
};
KSYS_CHECK_SIZE_NX150(EventSystem, 0x148);

}  // namespace ksys::evt
