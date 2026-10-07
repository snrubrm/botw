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
