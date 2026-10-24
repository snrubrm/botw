#include "gsys/gsysModelNW.h"
#include "gsys/gsysModelRenderUnitNW.h"
#include "gsys/gsysModelDynamicEnvInfo.h"
#include <g3d/aglNW4FToNN.h>
#include <nn/g3d/SkeletonObj.h>
#include <nn/g3d/ResModel.h>
#include <nn/util/util_ResDic.h>

namespace gsys {
ModelNW::CreateArg::CreateArg() : model(nullptr), buffer_num(1), _c(-1), _10(nullptr), _18(true), _19(true) {}
bool ModelNW::initialize(nn::g3d::ResModel* model, s32 buffer_num, sead::Heap* heap) {
    CreateArg arg;
    arg.model = model;
    arg.buffer_num = buffer_num;
    return initialize(arg, heap);
}


// 0x7100c05248
void ModelNW::clearTexture(int index) {
    agl::g3d::MaterialObj::ClearTexture(mModelObj.GetMaterial(index));
}

// 0x7100c06950
bool ModelNW::check(BoolType type) const {
    switch (static_cast<s32>(type)) {
    case 0:
        return (_200 & 0x40) != 0;
    case 1:
        return (_200 & 0x20) != 0;
    }
    return false;
}

// 0x7100c07b80
int ModelNW::getShapeNum() const {
    return mModelObj.GetNumShapes();
}

// 0x7100c07b88
int ModelNW::getViewNum() const {
    return mModelObj.GetNumViews();
}

// 0x7100c07b90
void ModelNW::createRenderUnitNW(int index, sead::Heap* heap) {
    allocAndInitRenderUnitNW(index, heap);
}

// 0x7100f1d514
int ModelNW::searchMaterialIndex(const char* material_name) const {
    const nn::util::ResDic* dict = mMaterialDic;
    if (dict == nullptr)
        return nn::util::ResDic::Npos;
    return dict->FindIndex(material_name);
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


sead::SafeString ModelNW::getName() const {
    return mModelObj.GetResource()->GetName();
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

void ModelNW::safeGetBoneWorldMatrix(sead::Matrix34f* matrix, int bone_idx) const {
    getBoneWorldMatrix(matrix, bone_idx);
}

void ModelNW::setDisplayListDirty() {
    _201 = (_201 & 0xf0) | ((1 << mBufferNum) + 0xff);

    int num = getModelRenderUnitNum();
    for (int i = 0; i < num; ++i)
        mRenderUnits[i]->updateCalcDisplayListMask();
}

void ModelNW::setDisplayListDirty(int index) {
    _201 = (_201 & 0xf0) | ((1 << mBufferNum) + 0xff);
    mRenderUnits[index]->updateCalcDisplayListMask();
}

ModelRenderUnit* ModelNW::getModelRenderUnit(int idx) {
    return mRenderUnits[idx];
}

const ModelRenderUnit* ModelNW::getModelRenderUnit(int idx) const {
    return mRenderUnits[idx];
}

}  // namespace gsys
