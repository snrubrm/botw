#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

namespace ksys::gfx {

// Name from the CSV rows at 0x7100f0bc9c .. 0x7100f15930 (initialize, destroy, calc, draw,
// getDrawLightNum, genMessage, ...). The class is the terrain pass's pre-pass light manager; only
// the part the draw-light getter needs is modelled so far. The other members keep their offsets.
class PrePassLightMgr {
public:
    // 0x7100f15738 (CSV name): the draw-light count of view `index` (with the buffer's bounds
    // fallback).
    u32 getDrawLightNum(s32 index) const;

private:
    u8 _0[0x28];
    sead::Buffer<u32> mDrawLightNums;
};

}  // namespace ksys::gfx
