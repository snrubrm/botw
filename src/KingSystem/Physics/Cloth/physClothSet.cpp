#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// 0x71026520ba8 (placeholder name): read by sub_7101218BCC when it re-enables the entries.
KSYS_VISIBILITY_HIDDEN bool sUnk_71026520BA8;

// NON_MATCHING: the original loads the entry count after the flag word; ours hoists it above the bool
// computation and is 4 bytes shorter.
void ClothSet::sub_7101218BCC(bool enabled) {
    const u32 flags = _70;
    if (!enabled && _60 >= 1.0f) {
        _70 = flags & ~u32(0x2000);
        const bool cloth_enabled = ((flags & 0x4000) | u32(sUnk_71026520BA8)) != 0;
        const s32 count = _18.size();
        for (s32 i = 0; i < count; ++i)
            sub_7101218C70(i, cloth_enabled);
        return;
    }
    _70 = flags | 0x2000;
    sub_7101218A90();
}

void ClothSet::sub_7101218A90() {
    const s32 count = _18.size();
    for (s32 i = 0; i < count; ++i) {
        _18[i]._30 = 0;
        _18[i]._18 &= ~u32(2);
        _18[i]._18 |= 4;
        const s32 num = _18[i]._8.size();
        for (s32 j = 0; j < num; ++j)
            sub_1409FC8(_18[i]._8[j]._8);
    }
    _5c = 0;
    _60 = 0;
}

void ClothSet::sub_71012189B8(bool enabled) {
    const s32 count = _18.size();
    for (s32 i = 0; i < count; ++i) {
        if (enabled) {
            if ((_18[i]._18 & 8) == 0) {
                _18[i]._18 |= 1;
                _18[i]._18 |= 2;
            } else {
                _18[i]._18 &= ~u32(1);
            }
        } else {
            _18[i]._18 &= ~u32(1);
        }
    }
}

s32 ClothSet::sub_71012193C4(const sead::SafeString& name) {
    const s32 count = _18.size();
    for (s32 i = 0; i < count; ++i) {
        if (name == sead::SafeString(_18[i]._0->_10->mName.cString()))
            return i;
    }
    return -1;
}

void ClothSet::sub_710121C26C(s32 cloth_index, s32 item_index, f32 value) {
    if (cloth_index >= _18.size())
        return;
    ClothDataUnk* data = _18[cloth_index]._0->_20->_0->_10;
    if (item_index < data->mNumParticles)
        data->mParticles[item_index]._8 = value;
}

}  // namespace ksys::phys
