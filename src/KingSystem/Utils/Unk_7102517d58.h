#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Types.h"

// Placeholder name for the flag object embedded at Controller +0x90. Its complete
// vtable at 0x7102517d58 contains only D1/D0 (0x7101266e98 / 0x7101266e9c).
class Unk_7102517d58 {
public:
    // Placeholder SEAD_ENUM: the flag bit index (a controller id). The original passes it by value
    // as a four-byte class: callers zero-extend the register with `and x1, #0xffffffff` and the
    // callee spills it before the volatile int() conversion. Values 0, 5 and 0xb are used.
    SEAD_ENUM(Id, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11);

    // 0x7101266e80; Controller constructs its next member at +0xa0.
    Unk_7102517d58();
    virtual ~Unk_7102517d58();
    // 0x7101266ea0: empty update called by Controller::calc.
    void sub_7101266EA0();
    // Bit `bit` of mFlags.
    bool isOnBit(Id bit) const;
    // 0x7101266ecc: sets / clears bit `bit` of mFlags.
    void setBit(Id bit, bool on);

private:
    sead::BitFlag32 mFlags;
};
KSYS_CHECK_SIZE_NX150(Unk_7102517d58, 0x10);
