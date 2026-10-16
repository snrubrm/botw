#include "KingSystem/Physics/Cloth/physClothSet.h"

namespace ksys::phys {

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
