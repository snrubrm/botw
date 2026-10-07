#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

struct SaveSlot;

// Placeholder name (CSV AlbumInfo::*; the object at SaveSystem + 0x1880): the album picture bookkeeping of the save
// system. Layout from the methods only: a bit set of the used picture values at +4 (0x1b0 bits), a 0xc0-byte block
// that is copied from / to the save slots at +0x3c. The size is not known (0x1880 .. 0x1a00 is assumed).
class AlbumInfo {
public:
    // 0x710090c954: the picture index flag `index`.
    s32 sub_710090C954(s32 index) const;
    // 0x710090c960: sets the picture index flag `index` to `value` and marks `value` as used.
    void sub_710090C960(s32 index, s32 value);
    // 0x710090ccb8: sets the picture size flag `index` to `size`.
    void sub_710090CCB8(s32 index, s32 size);
    // 0x710090ccc4: the first of the 48 picture slots without a picture (-1 if all are used).
    void sub_710090CCC4(s32* out) const;
    // 0x710090cd14: the first of the 48 picture slots whose index flag is `value`.
    void sub_710090CD14(s32* out, s32 value) const;
    // 0x710090cd68 / 0x710090cd84: copy the data block from / to `slot` (when `a` is set only if the slot's flag is set).
    void sub_710090CD68(const SaveSlot* slot, bool a);
    void sub_710090CD84(SaveSlot* slot, bool a) const;

private:
    u8 _0;
    u32 mUsedBits[14];
    u8 mData[0xc0];
    u8 _fc[0x180 - 0xfc];
};
KSYS_CHECK_SIZE_NX150(AlbumInfo, 0x180);

}  // namespace uking
