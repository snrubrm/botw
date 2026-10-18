#include "gsys/gsysModelRenderUnit.h"

namespace gsys {

ModelRenderUnit::ModelRenderUnit() = default;

ModelRenderUnit::~ModelRenderUnit() = default;

bool ModelRenderUnit::initialize(const ModelUnit* unit, int index, sead::Heap* heap) {
    mModelUnit = unit;
    mMaterialIndex = index;
    mIndex = index;
    return true;
}

}  // namespace gsys
