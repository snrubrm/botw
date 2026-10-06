#pragma once

#include <basis/seadTypes.h>

namespace ksys::phys {

// Placeholder: the object at CharacterController::_38 + 8 .. (CharacterController::_40; only the fields read / written
// by the accessors).
struct CharacterControllerUnk40 {
    // 0x7100f6693c (out of line in the original, in its own file so that it is not inlined into its callers).
    void sub_7100F6693C(bool value);

    /* 0x00 */ u8 _0[0x10];
    /* 0x10 */ s32 _10;
    /* 0x14 */ u8 _14[0x50];
    /* 0x64 */ u32 _64;
    /* 0x68 */ u8 _68;
    /* 0x69 */ bool _69;
    /* 0x6a */ bool _6a;
    /* 0x6b */ u8 _6b;
    /* 0x6c */ bool _6c;
    /* 0x6d */ u8 _6d;
    /* 0x6e */ u8 _6e;
    /* 0x6f */ u8 _6f;
    /* 0x70 */ u8 _70;
};

}  // namespace ksys::phys
