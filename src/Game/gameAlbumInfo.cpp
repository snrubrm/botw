#include "Game/gameAlbumInfo.h"
#include <cstring>
#include "Game/gameSaveSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking {

s32 AlbumInfo::sub_710090C954(s32 index) const {
    return ksys::gdt::getFlag_AlbumPictureIndex(index, false);
}

void AlbumInfo::sub_710090C960(s32 index, s32 value) {
    ksys::gdt::setFlag_AlbumPictureIndex(value, index, false);
    if (u32(value) <= 0x1af)
        mUsedBits[u32(value) >> 5] |= 1u << (u32(value) & 0x1f);
}

void AlbumInfo::sub_710090CCB8(s32 index, s32 size) {
    ksys::gdt::setFlag_AlbumPictureSize(size, index, false);
}

void AlbumInfo::sub_710090CCC4(s32* out) const {
    *out = -1;
    for (u32 i = 0; i < 0x30; ++i) {
        if (ksys::gdt::getFlag_AlbumPictureIndex(i, false) == -1) {
            *out = i;
            return;
        }
    }
}

void AlbumInfo::sub_710090CD14(s32* out, s32 value) const {
    for (u32 i = 0; i < 0x30; ++i) {
        if (ksys::gdt::getFlag_AlbumPictureIndex(i, false) == value) {
            *out = i;
            return;
        }
    }
}

void AlbumInfo::sub_710090CD68(const SaveSlot* slot, bool a) {
    if (!a || slot->_300)
        std::memcpy(mData, slot, sizeof(mData));
}

void AlbumInfo::sub_710090CD84(SaveSlot* slot, bool a) const {
    if (!a || slot->_300)
        std::memcpy(slot, mData, sizeof(mData));
}

}  // namespace uking
