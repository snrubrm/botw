#include <gsys/gsysModelUnitDrawArray.h>
#include <gsys/gsysModelDrawObj.h>
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

// 0x7100c49954
void ModelUnitDrawArray::flushUBO(s32 index) {
    sead::Matrix34f matrix;
    sead::Vector3f scale;
    mModelUnit->getBoneLocalMatrix(&matrix, &scale, 0);
    matrix.scaleBases(scale.x, scale.y, scale.z);

    ModelDrawObj* obj = static_cast<ModelDrawObj*>(mUnits[index]);
    for (int i = 0; i < obj->_c; i++) {
        obj->updateMtx(mModelUnit->_50->getCenter(), mModelUnit->_50->getRadius(), matrix);
    }
}

// 0x7100c49694
void ModelUnitDrawArray::reset_() {
    _68 &= ~8;
    for (int i = 0; i < mModelUnit->getMaterialNum(); i++) {
        if (((u32(mModelUnit->getMaterialInfo()[i]._a) & 7) - 2) <= 2) {
            _68 |= 8;
            return;
        }
    }
}

}  // namespace gsys
