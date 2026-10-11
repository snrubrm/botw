#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

// Native EventFlowMgr constructor owns two arrays of 0x18-byte entries (DBE0AC).
class EventMgrStruct3A {
public:
    EventMgrStruct3A();
    ~EventMgrStruct3A();
    void assignToActor(act::Actor* actor);

    /* 0x00 */ act::Actor* mActor = nullptr;
    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ bool mAssigned = false;
    /* 0x11 */ bool mHasUniqueName = false;
};
static_assert(sizeof(EventMgrStruct3A) == 0x18);

// Native DC12A4 initializes the 0x190-byte records owned by EventFlowMgr.
class EventMgrStruct3B {
public:
    EventMgrStruct3B();

    /* 0x000 */ sead::FixedSafeString<64> _0;
    /* 0x058 */ s32 _58 = 0;
    u8 _5c[0x160 - 0x5c];
    /* 0x160 */ s32 _160 = 0;
    /* 0x164 */ s32 _164 = 3;
    /* 0x168 */ s32 _168 = 0;
    /* 0x170 */ void* _170 = nullptr;
    /* 0x178 */ s32 _178 = 0;
    /* 0x17c */ sead::Vector2f _17c = sead::Vector2f::zero;
    /* 0x184 */ sead::Vector2f _184 = sead::Vector2f::zero;
};
static_assert(sizeof(EventMgrStruct3B) == 0x190);

}  // namespace ksys::evt
