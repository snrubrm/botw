#include <gsys/gsysModelUnitDrawArray.h>

namespace gsys {

ModelUnitDrawArray::CreateArg::CreateArg() {
    _0 = 1;
    _4 = 0x101;
}

bool ModelUnitDrawArray::isZSortEnabled() const {
    return (_68 & 2) != 0;
}


s32 ModelUnitDrawArray::getSize() const {
    return mSize;
}

}  // namespace gsys
