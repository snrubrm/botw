#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include "KingSystem/Utils/Types.h"

namespace aal {
class Shape;
}

namespace ksys::phys {
class RigidBody;
}

namespace ksys::act {
class Actor;
}

namespace sead {
class Heap;
}

// Placeholder name = vtable address (0x710250c260; constructor 0x71010c3588, D1 0x71010c35e4, D0
// 0x71010c3644). Sensor body helper embedded in ExpandSensor / ExpandSensorSlowly (+0x48 in the latter): owns
// a rigid body (created by 0x71010c36a4, not decompiled) which the destructor removes from the world and
// deletes. No RTTI.
class Unk_710250c260 {
public:
    Unk_710250c260();
    virtual ~Unk_710250c260();

    // 0x71010c36a4 (declared only): creates the sensor body.
    void sub_71010C36A4(f32 a1, f32 a2, const sead::Matrix34f* mtx, sead::Heap* heap,
                        ksys::act::Actor* actor);

    // 0x71010c38f4 (declared only; ExpandSensor::enter_ passes the actor's home matrix).
    void sub_71010C38F4(const sead::Matrix34f* mtx);
    // 0x71010c3a1c (declared only; ExpandSensor::enter_ passes the capsule radius).
    void sub_71010C3A1C(f32 radius);
    // 0x71010c3b18 (declared only; ExpandSensor::enter_ passes the capsule length `_d4`).
    void sub_71010C3B18(f32 length);

    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ ksys::phys::RigidBody* mBody = nullptr;
    /* 0x18 */ u32 _18 = 0;
    /* 0x20 */ void* _20 = nullptr;
    /* 0x28 */ sead::Matrix34f _28 = sead::Matrix34f::ident;
    /* 0x58 */ f32 _58 = 1.0f;
    /* 0x5c */ f32 _5c = 1.0f;
    /* 0x60 */ void* _60 = nullptr;
    /* 0x68 */ u32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710250c260, 0x70);

// Placeholder name = vtable address (0x710250c3c8; constructor 0x71010c3f50, D1 0x71010c3f90, D0
// 0x71010c420c). Wind capsule helper embedded in WindControl / ForkCapsuleWindFollow (+0x40): an effect
// object (`_8`), a sensor body (`mBody`), an xlink2 event (`_58`, id in `_60`) and an aal::Shape (`mShape`).
class Unk_710250c3c8 {
public:
    Unk_710250c3c8();
    virtual ~Unk_710250c3c8();

    // 0x71010c4008 (declared only; 516 B): releases the effect / body / event.
    void destroy(bool remove_links);
    // 0x71010c42b4 (declared only; 488 B).
    void sub_71010C42B4();
    // 0x71010c4284: true if the body was removed from the world (or there is none). Placeholder name.
    bool sub_71010C4284() const;

    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ ksys::phys::RigidBody* mBody = nullptr;
    /* 0x18 */ bool _18 = false;
    /* 0x1c */ f32 _1c = 1.0f;
    /* 0x20 */ u8 _20[0x50 - 0x20];
    /* 0x50 */ f32 _50 = 1.0f;
    /* 0x54 */ f32 _54 = 1.0f;
    /* 0x58 */ void* _58 = nullptr;
    /* 0x60 */ u32 _60 = 0;
    /* 0x68 */ void* _68 = nullptr;
    /* 0x70 */ u32 _70 = 0;
    /* 0x78 */ aal::Shape* mShape = nullptr;
    /* 0x80 */ bool _80 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710250c3c8, 0x88);
