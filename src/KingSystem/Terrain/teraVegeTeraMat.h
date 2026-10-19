#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::tera {

// Placeholder: the 0x530-byte vegetation terrain material the three helpers below
// operate on. Its constructor is 0x7101078838 (CSV VegeTeraMat::ctor).
struct VegeTeraMat {
    u32 _0;
    u8 _4[0x530 - 0x4];
};
static_assert(sizeof(VegeTeraMat) == 0x530);

// Placeholder: the container at 0x7101078674 / 0x710107869c / 0x71010786f4. It holds three
// VegeTeraMat records at +8 / +0x538 / +0xa68 (stride 0x530).
class VegeTeraMatMgr {
public:
    // 0x7101078674: marks all three records dirty.
    void setDirty();
    // 0x710107869c: forwards `value` to each record unless the global gate is set.
    void sub_710107869C(u8 value);
    // 0x71010786f4: runs the no-argument update on each record unless the global gate is set.
    void sub_71010786F4();

private:
    u8 _0[8];
    VegeTeraMat mRecords[3];
};
KSYS_CHECK_SIZE_NX150(VegeTeraMatMgr, 0xf98);

}  // namespace ksys::tera
