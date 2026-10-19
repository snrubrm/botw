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
    // Placeholder: the 0x90-byte buffer entries and the item they point at.
    struct Item {
        u8 _0[0x20];
        u8 mFlags;
    };
    struct Entry {
        Item* mItem;
        u8 _8[8];
        u8 _10[0x80];
    };
    static_assert(sizeof(Entry) == 0x90);
    struct Buffer {
        u8 _0[0xd8];
        s32 mCount;
        u8 _dc[4];
        Entry* mArray;
    };
    static_assert(offsetof(Buffer, mCount) == 0xd8);
    static_assert(offsetof(Buffer, mArray) == 0xe0);

    // 0x7101078674: marks all three records dirty.
    void setDirty();
    // 0x710107869c: forwards `value` to each record unless the global gate is set.
    void sub_710107869C(u8 value);
    // 0x71010786f4: runs the no-argument update on each record unless the global gate is set.
    void sub_71010786F4();
    // 0x710107873c: forwards the selected buffer entry to each record unless the global gate is set.
    void sub_710107873C(void* arg);

private:
    u8 _0[8];
    VegeTeraMat mRecords[3];
    // Read by the per-record update 0x710107873c: an index and the buffer whose 0x90-byte
    // entries it indexes (count at +0xd8, array at +0xe0).
    // inline-only in the original: 0x710107873c reloads the selected entry before each call.
    Entry* getEntry() {
        const s32 index = _f9c;
        return u32(_fa0->mCount) > u32(index) ? &_fa0->mArray[index] : _fa0->mArray;
    }

    u8 _f98[4];
    s32 _f9c;
    Buffer* _fa0;
};
KSYS_CHECK_SIZE_NX150(VegeTeraMatMgr, 0xfa8);

}  // namespace ksys::tera
