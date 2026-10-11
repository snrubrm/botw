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

}  // namespace ksys::phys
