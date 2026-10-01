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

}  // namespace ksys::phys
