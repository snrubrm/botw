#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

// The full 0x7100e726a8 receiver reads six float parameter pointers and passes
// its three scalar state fields to 0x7100e72498. NpcSwimMove::calc_ passes +0xa0.
struct Unk_7100e726a8 {
    f32 sub_7100E726A8(f32 value);

    const f32* _0;
    const f32* _8;
    const f32* _10;
    const f32* _18;
    const f32* _20;
    const f32* _28;
    f32 _30;
    f32 _34;
    f32 _38;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e726a8, 0x40);
