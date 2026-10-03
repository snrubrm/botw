#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Types.h"

namespace uking::act {

// Name from the CSV (ExtendedEntity::ctor 0x7100e63b5c, ExtendedEntity::init 0x7100e63ba4; empty
// out-of-line destructor 0x7100e63ba0). Size 0x70. Embedded in HorseBase (0xa98).
// init copies 16 floats (0x20-0x5c) from its argument.
// TODO: incomplete.
class ExtendedEntity {
public:
    // Placeholder (bits of _58; callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)

    ExtendedEntity();
    ~ExtendedEntity();

    /* 0x00 */ void* _0 = nullptr;
    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ void* _18 = nullptr;
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
    /* 0x60 */ void* _60 = nullptr;
    /* 0x68 */ u32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(ExtendedEntity, 0x70);

}  // namespace uking::act
