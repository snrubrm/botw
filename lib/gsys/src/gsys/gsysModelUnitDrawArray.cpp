#include <gsys/gsysModelUnitDrawArray.h>
#include <gsys/gsysModelUnit.h>

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

// 0x7100c495e8
void ModelUnitDrawArray::setSize(s32 size) {
    ModelUnit* unit = mModelUnit;
    mSize = size;
    unit->mCalcWeight = unit->getModelRenderUnitNum() + size;
}

}  // namespace gsys
