#include "gsys/gsysModelRenderUnitNW.h"
#include <basis/seadNew.h>
#include <new>
#include <nn/g3d/ModelObj.h>
#include "gsys/gsysModelNW.h"

namespace gsys {

void ModelRenderUnitNW::setPolygonCtrl(u32 value) {
    mPolygonCtrl = value;
}


// 0x7100c09fcc
void ModelRenderUnitNW::createShapeRecords(sead::Heap* heap) {
    const int shape_num = mModelUnit->getShapeNum();
    mShapeRecords = new (heap, 8) ShapeRecord[shape_num];
    for (int i = 0; i < shape_num; ++i) {
        mShapeRecords[i]._0 = nullptr;
        mShapeRecords[i]._8 = nullptr;
        mShapeRecords[i]._10 = 0xff;
    }
}

// 0x7100c0a098
void ModelRenderUnitNW::updateCalcDisplayListMask() {
    const auto* model = static_cast<const ModelNW*>(mModelUnit);
    const u8 buffer_num = model->mBufferNum;
    mCalcDisplayListMask = (1 << buffer_num) - 1;
}

// 0x7100c09d28
nn::g3d::ShapeObj* ModelRenderUnitNW::getShape() const {
    auto* model = const_cast<ModelNW*>(static_cast<const ModelNW*>(mModelUnit));
    return model->getModelObj()->GetShape(mIndex);
}

// 0x7100c09d60
nn::g3d::MaterialObj* ModelRenderUnitNW::getMaterial() const {
    auto* model = const_cast<ModelNW*>(static_cast<const ModelNW*>(mModelUnit));
    return model->getModelObj()->GetMaterial(mMaterialIndex);
}

s32 ModelRenderUnitNW::getPassTextureBit() const {
    return _220;
}

s32 ModelRenderUnitNW::getType() const {
    return 0;
}

namespace {
const s32 kPriorityHint[] = {0, 6, 5, 7, 2, 3, 4, 1, 1};
}

s32 ModelRenderUnitNW::getPriorityHintFromType(ModelEnum::PriorityHintType type, bool invert) {
    const s32 value = kPriorityHint[static_cast<u32>(type)];
    return invert ? -value : value;
}

}  // namespace gsys
