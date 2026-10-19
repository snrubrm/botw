#include "gsys/gsysModelRenderUnit.h"

namespace gsys {

bool ModelRenderUnit::calcViewFrustumCulling(int, int, int, const agl::cull::ViewFrustumCulling&,
                                            const nn::g3d::ViewVolume&, float*) {
    return true;
}


ModelRenderUnit::ModelRenderUnit() = default;

ModelRenderUnit::~ModelRenderUnit() = default;

bool ModelRenderUnit::initialize(const ModelUnit* unit, int index, sead::Heap* heap) {
    mModelUnit = unit;
    mMaterialIndex = index;
    mIndex = index;
    return true;
}

}  // namespace gsys
