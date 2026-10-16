#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

// Placeholder name: the scalar smoother updated by 0x7100e7277c.
// Unk_7100000fd0 embeds it at +0x40; the coefficient is supplied by a parameter pointer.
struct Unk_7100e7277c {
    f32 sub_7100E7277C(f32 target);

    const f32* _0;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e7277c, 0x10);

// Placeholder name: a scalar smoother with an inline coefficient (0x7100e726e0); HorseRiddenByPlayer
// keeps one at +0x234.
struct Unk_7100e726e0 {
    // Moves _4 towards `target` by the frame-rate independent factor (1 - _0) ^ delta.
    void sub_7100E726E0(f32 target);

    f32 _0;
    f32 _4;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e726e0, 0x8);
