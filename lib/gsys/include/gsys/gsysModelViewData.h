#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// Placeholder: one record of the procedural draw's per-view array (0x3b8 bytes). Core's per-view
// update 0x71013021e0 indexes the array and reads the u16 state index at +0; the remaining view
// data (matrices, frustum) is not modelled yet.
class ModelViewData {
public:
    /* 0x000 */ u16 _0;
    u8 _2[0x3b8 - 0x2];
};
static_assert(sizeof(ModelViewData) == 0x3b8);

}  // namespace gsys
