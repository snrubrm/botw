#pragma once

#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

// Placeholder name for the flag object embedded at Controller +0x90. Its complete
// vtable at 0x7102517d58 contains only D1/D0 (0x7101266e98 / 0x7101266e9c).
class Unk_7102517d58 {
public:
    // 0x7101266e80; Controller constructs its next member at +0xa0.
    Unk_7102517d58();
    virtual ~Unk_7102517d58();
    // 0x7101266ea0: empty update called by Controller::calc.
    void sub_7101266EA0();

private:
    sead::BitFlag32 mFlags;
};
KSYS_CHECK_SIZE_NX150(Unk_7102517d58, 0x10);
