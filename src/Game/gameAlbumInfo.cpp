#include "Game/gameAlbumInfo.h"
#include <cstring>
#include "Game/gameSaveSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"

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

// NON_MATCHING: the structure and the unrolling of the duplicate removal loop match; the original branches on
// `indices[j] != -1` and `current == indices[j]` separately (no ccmp) and keeps the SaveSystem instance in a register
s32 AlbumInfo::sub_710090C9B4(s32 value) {
    auto* save_system = SaveSystem::instance();
    if (!_0 && ksys::gdt::Manager::instance() && save_system) {
        for (auto& bits : mUsedBits)
            bits = 0;

        for (s32 slot_idx = 0; slot_idx < 8; ++slot_idx) {
            auto* slot = save_system->sub_7100914DA0(slot_idx);
            if (slot->_300) {
                for (s32 i = 0; i < 0x30; ++i)
                    markUsed_(slot->mAlbumIndices[i]);
            }
        }
        for (s32 i = 0; i < 0x30; ++i)
            markUsed_(mIndices[i]);
        _0 = 1;
    }

    if (!(mUsedBits[value >> 5] & (1u << (value & 0x1f))))
        return -1;

    s32 indices[0x30] = {-1};
    bool removed = false;
    for (s32 i = 0; i < 0x30; ++i) {
        s32 current = ksys::gdt::getFlag_AlbumPictureIndex(i, false);
        indices[i] = current;
        for (s32 j = 0; j < i; ++j) {
            if (current != -1) {
                if (indices[j] != -1 && current == indices[j]) {
                    indices[i] = -1;
                    removed |= indices[j] == value;
                    current = -1;
                }
            }
        }
    }

    if (!removed)
        return ksys::gdt::getFlag_AlbumPictureSize(value, false);

    s32 read = 0;
    for (s32 write = 0; write < 0x30; ++write) {
        s32 index = -1;
        while (read < 0x30) {
            if (indices[read] != -1) {
                index = indices[read];
                break;
            }
            ++read;
        }
        ksys::gdt::setFlag_AlbumPictureIndex(index, write, false);
    }
    return -1;
}

// NON_MATCHING: the original keeps the `value >= 0 && value < 0x1b0` mark checks as a sign test plus
// an unsigned compare; ours merges them, and its stack frame keeps x23 instead of x22.
u32 AlbumInfo::getFreePictureIndexMaybe() {
    if (!_0) {
        if (ksys::gdt::Manager::instance() && SaveSystem::instance()) {
            for (u32& bits : mUsedBits)
                bits = 0;
            for (s32 i = 0; i < 8; ++i) {
                SaveSlot* slot = SaveSystem::instance()->sub_7100914DA0(i);
                if (!slot->_300)
                    continue;
                for (s32 j = 0; j < 0x30; ++j)
                    markUsed_(slot->mAlbumIndices[j]);
            }
            for (s32 i = 0; i < 0x30; ++i)
                markUsed_(mIndices[i]);
            _0 = true;
        }
    }

    u32 index = 0xffffffff;
    for (s32 i = 0; i < 14; ++i) {
        const u32 bits = mUsedBits[i];
        if (bits == 0xffffffff)
            continue;
        for (s32 b = 0; b < 32; ++b) {
            if (!(bits & (1u << b)))
                index = u32(i * 32 + b);
        }
        break;
    }
    return index < 0x1b0 ? index : 0xffffffff;
}

void AlbumInfo::sub_710090CD68(const SaveSlot* slot, bool a) {
    if (!a || slot->_300)
        std::memcpy(mIndices, slot->mAlbumIndices, sizeof(mIndices));
}

void AlbumInfo::sub_710090CD84(SaveSlot* slot, bool a) const {
    if (!a || slot->_300)
        std::memcpy(slot->mAlbumIndices, mIndices, sizeof(mIndices));
}

}  // namespace uking
