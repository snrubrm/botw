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

s32 ModelRenderUnit::getMeshNum() const {
    return 1;
}

s32 ModelRenderUnit::getSubMeshNum(int) const {
    return 1;
}

bool ModelRenderUnit::getSubMeshBoundAABB(int, int, sead::BoundBox3f*) const {
    return false;
}

void ModelRenderUnit::getBoundSphereImpl(sead::Sphere3f* sphere) const {
    sphere->setCenter(sead::Vector3f::zero);
    sphere->setRadius(sead::Mathf::maxNumber());
}

s32 ModelRenderUnit::getPassTextureBit() const {
    return 0;
}

bool ModelRenderUnit::isVisible() const {
    return true;
}

}  // namespace gsys
