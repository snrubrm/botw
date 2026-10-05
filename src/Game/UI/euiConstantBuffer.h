#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace eui {

// Per-frame constant buffer of the UI renderer (owned by the ScreenMgr at 0xb48; size not known).
class ConstantBuffer {
public:
    // 0x7100bf42f8 / 0x7100bf4364
    void map();
    void unmap();

    // inline in ScreenMgr::update (0x7100bec514); name is a guess: toggles the buffer index that map() uses
    void swapIndex() { mIndex = 1 - mIndex; }

private:
    u8 _0[0x1a8];
    /* 0x1a8 */ s8 mIndex;
    /* 0x1a9 */ bool _1a9;
    /* 0x1aa */ bool _1aa;
};

}  // namespace eui
