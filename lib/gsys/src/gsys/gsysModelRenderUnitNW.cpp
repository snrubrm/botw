#include "gsys/gsysModelRenderUnitNW.h"
#include <nn/g3d/ModelObj.h>
#include "gsys/gsysModelNW.h"

namespace gsys {

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

}  // namespace gsys
