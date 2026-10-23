#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

// 0x710107e060: toggles bit 30 of _328 and swaps the two alternating patch buffers.
void MapPatcher::sub_710107E060() {
    const u32 mask = 0x40000000;
    const u32 flags = _328;
    _328 = (flags & mask) == 0 ? flags | mask : flags & ~mask;
    const u32 index = (_328 >> 30) & 1;
    const u32 other = index ^ 1;
    u8* const selected = _2d8[index];
    u8* const alternate = _2d8[other];
    _300 = selected;
    _2f8 = alternate;
}

}  // namespace ksys::tera
