#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace ksys {
class MessageTransceiverTxOnly;
}

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}

namespace ksys::evt {

class EventFlowBase;

// The current speaker of the event system (EventSystem + 0xc0; CSV evt::S3, placeholder name).
class EventSpeaker {
public:
    // 0x7100e496ac (CSV evt::S3::ctor)
    EventSpeaker();
    // D1 0x71008aa750 (CSV evt::EventSystem::x_6), D0 0x71008ac2a0
    virtual ~EventSpeaker() = default;

    // 0x7100e49784 (placeholder name): releases the speaker link under the lock
    void sub_7100E49784();
    // 0x7100e496f0 (CSV evt::S3::updateActorPosition): copies the previous / current position of the linked actor
    void updateActorPosition();
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

    // 0x71008ac118 (placeholder name): whether the active event flow has the byte-3 flag (the object is unused)
    bool sub_71008AC118() const;
    // 0x71008ac078 (CSV x_2): sets the scene freeze state `_140` (Root38 flag 3, the load / save icon)
    void x_2(s32 value);
    // 0x71008ac100 (CSV x_3): sets bit 5 of the global scene flag word
    void x_3(bool value);
    // 0x71008abf30 / 0x71008abf38 (placeholder names): release the speaker link / acquire the speaker actor
    void sub_71008ABF30();
    void sub_71008ABF38(act::ActorConstDataAccess* accessor);

    // 0x71008ac1bc (CSV x?: __auto0; placeholder name): counts the event flow `flow` (by its flags), see S7
    void sub_71008AC1BC(EventFlowBase* flow);
    // 0x71008ac148 (CSV __auto1; placeholder name): takes the event flow out of the count
    void sub_71008AC148(EventFlowBase* flow);

    // 0x71008abf48: speaker assignment.
    bool setSpeaker(act::Actor* actor);

    /* 0x30 */ u16 _30 = 0;
    /* 0x32 */ u8 _32 = 0;
    u8 _33;
    /* 0x34 */ s32 _34 = 0;
    /* 0x38 */ s32 _38 = 0;
    /* 0x3c */ sead::SafeArray<bool, 9> _3c;
    /* 0x45 */ sead::SafeArray<bool, 9> _45;
    u8 _4e[2];
    /* 0x50 */ s32 _50;
    u8 _54[4];
    /* 0x58 */ Unk_710246c4d8 _58;
    /* 0x68 */ ActorMessageTransceiver mTransceiver{*this};
    /* 0xc0 */ EventSpeaker mSpeaker;
    /* 0x130 */ ksys::MessageTransceiverTxOnly* mTxTransceiver = nullptr;
    /* 0x138 */ s32 _138 = 0;
    /* 0x13c */ s32 _13c = 0;
    /* 0x140 */ s32 _140 = 0;
    /* 0x144 */ u16 _144 = 0;
};
KSYS_CHECK_SIZE_NX150(EventSystem, 0x148);

}  // namespace ksys::evt
