#include "KingSystem/Physics/Cloth/physClothResource.h"
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>

namespace ksys::phys {

ClothResource::ClothResource() = default;

ClothResource::~ClothResource() {
    if (_40 && (_48 & 2))
        hkNativePackfileUtils::unloadInPlace(_20, mRawSize);
    _40 = nullptr;
    _28.freeBuffer();
    delete[] _20;
    _20 = nullptr;
}

s32 ClothResource::sub_710121CEA0() const {
    if (_48 & 1)
        return 1;
    if (_48 & 4)
        return 2;
    return (_48 & 8) ? 3 : (_48 & 0x10) ? 4 : (_48 & 0x20) ? 5 : 0;
}

}  // namespace ksys::phys
