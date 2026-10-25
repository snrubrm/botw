#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::phys {

// Placeholder: the object at CharacterController::_38 (only the fields read / written by the
// accessors are modelled). Its methods live in physCharacterControllerUnk38.cpp.
struct CharacterControllerUnk38 {
    /* 0x00 */ u8 _0[0x18];
    // Constructor f63cd0 and controller initialization f5dc88 prove the slope angle.
    /* 0x18 */ f32 _18;
    /* 0x1c */ sead::Vector3f _1c;
    /* 0x28 */ sead::Vector3f _28;
    /* 0x34 */ bool _34;
    /* 0x38 */ sead::Vector3f _38;
    /* 0x44 */ sead::Vector3f _44;
    /* 0x50 */ sead::Vector3f _50;
    void sub_7100F652F8(const sead::Vector3f& velocity);
    // 0x7100f653b0 (declaration only): the ground / edge check that reads the controller at _10.
    void sub_7100F653B0(const sead::Vector3f& a, const sead::Vector3f& b);
    // 0x7100f659fc (unnamed in the CSV): the check at _38 / _44, run only when _34 is set.
    void sub_7100F659FC();
};

}  // namespace ksys::phys
