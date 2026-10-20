#pragma once

#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {
class CharacterController;
class LimitHingeCs;
class RigidBody;
class Unk_71024f9510;
}

namespace uking::act {

// Name from the CSV (ExtendedEntity::ctor 0x7100e63b5c, ExtendedEntity::init 0x7100e63ba4; empty
// out-of-line destructor 0x7100e63ba0). Size 0x70. Embedded in HorseBase (0xa98).
// init copies fourteen settings (0x20-0x54) from its argument.
// TODO: incomplete.
class ExtendedEntity {
public:
    // Placeholder (bits of _58; callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)

    ExtendedEntity();
    ~ExtendedEntity();
    // 0x7100e63ba4 consumes the heap, both bodies, fourteen settings and an optional frame radius.
    struct InitArg {
        sead::Heap* heap;
        ksys::phys::CharacterController* controller;
        ksys::phys::RigidBody* body;
        sead::Vector3f _18;
        f32 _24;
        f32 _28;
        f32 _2c;
        f32 _30;
        f32 _34;
        f32 _38;
        f32 _3c;
        f32 _40;
        f32 _44;
        f32 _48;
        f32 _4c;
        f32 radius;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x58);
    bool init(const InitArg& arg);
    // 0x7100e63f70 resets and optionally attaches the entity at the controller transform.
    void sub_7100E63F70(const sead::Matrix34f& transform, bool attach);
    // 0x7100e64154 toggles participation and refreshes the body transform when enabled.
    void sub_7100E64154(bool disable);
    // 0x7100e64318 returns whether the body was repositioned; both trailing arguments are bools.
    bool sub_7100E64318(const sead::Matrix34f& transform, bool force, bool reset_rotation);
    void sub_7100E64E60();
    void sub_7100E64EAC(f32 scale);
    // 0x7100e63f20: releases the contact listener, the constraint and the frame data.
    void sub_7100E63F20();
    // 0x7100e64cdc: updates the hinge limits and the centre of mass from the frame data.
    void sub_7100E64CDC(f32 delta);
    // 0x7100e64de8: sets or clears flag _0; setting it also detaches the entity.
    void sub_7100E64DE8(bool on);

    // Placeholder name (allocated by init 0x7100e63ba4, 0x4c bytes): the six frame vectors the
    // limited hinge and the centre of mass use, plus the radius that init reads from its argument.
    struct FrameSet {
        /* 0x00 */ sead::Vector3f _0 = sead::Vector3f::zero;
        /* 0x0c */ sead::Vector3f _c = sead::Vector3f::zero;
        /* 0x18 */ sead::Vector3f _18 = sead::Vector3f::ez;
        /* 0x24 */ sead::Vector3f _24 = sead::Vector3f::ez;
        /* 0x30 */ sead::Vector3f _30 = sead::Vector3f::ey;
        /* 0x3c */ sead::Vector3f _3c = sead::Vector3f::ey;
        /* 0x48 */ f32 _48 = 0;
    };
    static_assert(sizeof(FrameSet) == 0x4c);

    /* 0x00 */ ksys::phys::CharacterController* _0 = nullptr;
    /* 0x08 */ ksys::phys::RigidBody* _8 = nullptr;
    /* 0x10 */ ksys::phys::LimitHingeCs* _10 = nullptr;
    /* 0x18 */ ksys::phys::Unk_71024f9510* _18 = nullptr;
    /* 0x20 */ sead::Vector3f _20 = sead::Vector3f::zero;
    /* 0x2c */ f32 _2c = 0;
    /* 0x30 */ f32 _30 = 0;
    /* 0x34 */ f32 _34 = 0;
    /* 0x38 */ f32 _38 = 0;
    /* 0x3c */ f32 _3c = 0;
    /* 0x40 */ f32 _40 = 0;
    /* 0x44 */ f32 _44 = 0;
    /* 0x48 */ f32 _48 = 0;
    /* 0x4c */ f32 _4c = 0;
    /* 0x50 */ f32 _50 = 0;
    /* 0x54 */ f32 _54 = 0;
    /* 0x58 */ u8 _58 = 0;  // flag bits, modified with raw `|= 1 << int(Flag(...))` (HorseDie::leave_)
    /* 0x60 */ FrameSet* _60 = nullptr;
    /* 0x68 */ f32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(ExtendedEntity, 0x70);

// 0x7100e64b60 (placeholder name): the signed angle of `a` around the Y axis relative to `b`.
f32 sub_7100E64B60(const sead::Vector3f& a, const sead::Vector3f& b);

}  // namespace uking::act
