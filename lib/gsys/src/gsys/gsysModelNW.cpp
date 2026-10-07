#include "gsys/gsysModelNW.h"
#include "gsys/gsysModelDynamicEnvInfo.h"
#include <nn/g3d/SkeletonObj.h>

namespace gsys {
ModelNW::CreateArg::CreateArg() : model(nullptr), buffer_num(1), _c(-1), _10(nullptr), _18(true), _19(true) {}
bool ModelNW::initialize(nn::g3d::ResModel* model, s32 buffer_num, sead::Heap* heap) {
    CreateArg arg;
    arg.model = model;
    arg.buffer_num = buffer_num;
    return initialize(arg, heap);
}


void ModelNW::getMaterialUserData(ModelNW** model, u16* material_index, const void* user_data) {
    const auto* data = static_cast<const MaterialUserData*>(user_data);
    if (model)
        *model = data->model;
    if (material_index)
        *material_index = data->material_index;
}

void ModelNW::calcBounding() {
    if ((_200 & 2) && _50 == &_40)
        calcBounding_();
}

void ModelNW::BoneVisibilityCallback(nn::g3d::ModelObj* obj, int) {
    auto* model = static_cast<ModelNW*>(obj->GetUserPtr());
    model->gatherVisibleModelRenderUnit();
    model->_200 |= 2;
}

void ModelNW::MaterialVisibilityCallback(nn::g3d::ModelObj* obj, int) {
    auto* model = static_cast<ModelNW*>(obj->GetUserPtr());
    model->gatherVisibleModelRenderUnit();
    model->_200 |= 2;
}


s32 ModelNW::getSubMeshRangeNum(s32 type, s32 count) {
    return type > 1 ? count + 1 : (count + 1) / 2 + 1;
}

agl::lght::LocalLightMapObj* ModelNW::getReferenceLocalLightMapObj() const {
    return mDynamicEnvInfo ? mDynamicEnvInfo->getReferenceLocalLightMapObj() : nullptr;
}


// 0x7100c06d30
sead::SafeString ModelNW::getBoneName(int bone_idx) const {
    return mModelObj.GetSkeleton()->GetRes()->GetBoneName(bone_idx);
}

// 0x7100c06dd8
void ModelNW::clearBoneLocalMatrix() {
    _200 |= 0x40;
    mModelObj.GetSkeleton()->ClearLocalMtx();
}

}  // namespace gsys
