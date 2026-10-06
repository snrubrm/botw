#pragma once

#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

// The current speaker of the event system (EventSystem + 0xc0; CSV evt::S3, placeholder name).
class EventSpeaker {
public:
    // 0x7100e497fc (CSV evt::S3::setSpeaker): replaces the speaker link; false if `actor` could not be linked.
    bool setSpeaker(act::Actor* actor);

    u8 _0[8];
    /* 0x08 */ act::BaseProcLink mLink;
    /* 0x18 */ sead::Vector3f mPreviousPos;
    /* 0x24 */ sead::Vector3f mPos;
    /* 0x30 */ sead::CriticalSection mCS;
};

// Partial declaration: CSV abbreviates the name as evt::EventSystem.
// Namespace inferred from the existing Manager/ActorFactory convention.
// No instance layout or construction is modeled here.
class EventSystem {
public:
    // Original instance pointer 0x71025d0c50 (GOT 0x710257b878).
    static EventSystem* instance() { return sInstance; }
    static EventSystem* sInstance;

    // 0x71008abf48: speaker assignment.
    bool setSpeaker(act::Actor* actor);

    u8 _0[0xc0];
    /* 0xc0 */ EventSpeaker mSpeaker;
};

}  // namespace ksys::evt
