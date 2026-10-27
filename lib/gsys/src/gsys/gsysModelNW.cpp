#include "gsys/gsysModelNW.h"
#include "gsys/gsysModelRenderUnitNW.h"
#include "gsys/gsysModelDynamicEnvInfo.h"
#include "gsys/gsysG3dResModelEx.h"
#include "gsys/gsysG3dResMaterialEx.h"
#include <g3d/aglNW4FToNN.h>
#include <heap/seadHeapMgr.h>
#include <prim/seadPtrUtil.h>
#include <new>
#include <nn/g3d/SkeletonObj.h>
#include <nn/g3d/ResModel.h>
#include <nn/g3d/ResMaterial.h>
#include <nn/util/util_ResDic.h>

namespace gsys {
ModelNW::CreateArg::CreateArg() : model(nullptr), buffer_num(1), _c(-1), _10(nullptr), _18(true), _19(true) {}
bool ModelNW::initialize(nn::g3d::ResModel* model, s32 buffer_num, sead::Heap* heap) {
    CreateArg arg;
    arg.model = model;
    arg.buffer_num = buffer_num;
    return initialize(arg, heap);
}


// 0x7100c06dec
int ModelNW::getMaterialNum() const {
    return mModelObj.GetNumMaterials();
}

// 0x7100c06f30
sead::SafeString ModelNW::getMaterialName(int index) const {
    return sead::SafeString(mModelObj.GetMaterial(index)->GetResource()->m_pName + 2);
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

// 0x7100c07b94
ModelRenderUnitNW* ModelNW::allocAndInitRenderUnitNW(int index, sead::Heap* heap) {
    RenderUnitInitData init;
    auto* unit = static_cast<ModelRenderUnitNW*>(
        createRenderUnit_(index, &init, sizeof(ModelRenderUnitNW), heap));
    if (!unit)
        return nullptr;
    new (unit) ModelRenderUnitNW;
    if (!initRenderUnit_(unit, index, init, heap))
        return nullptr;
    return unit;
}

// 0x7100c042e0
void* ModelNW::createRenderUnit_(int index, RenderUnitInitData* init, size_t size,
                                 sead::Heap* heap) {
    ModelRenderUnitNW* unit = mRenderUnits[index];
    if (unit) {
        init->reuse = true;
        init->flags = unit->getFlags10();
        for (s32 i = 0; i < 15; ++i)
            init->variations[i] = u8(unit->getShaderVariation(i));
        delete unit;
        mRenderUnits[index] = nullptr;
    }
    if (!heap)
        heap = sead::HeapMgr::sInstancePtr->getCurrentHeap();
    return heap->tryAlloc(size, 0x20);
}

// 0x7100c043a4
bool ModelNW::initRenderUnit_(ModelRenderUnitNW* unit, int index, const RenderUnitInitData& init,
                              sead::Heap* heap) {
    if (!unit->initialize(this, index, heap))
        return false;
    if (init.reuse) {
        unit->getFlags10() = init.flags;
        for (s32 i = 0; i < 15; ++i)
            unit->setShaderVariation(i, init.variations[i]);
    }
    mRenderUnits[index] = unit;
    return true;
}

// 0x7100c05414
void ModelNW::setLodLevelNum(int lod_level_num) {
    mNumLods = lod_level_num;
    _168 = u8((_168 & 0xe3) | (lod_level_num << 2));
    const int count = getModelRenderUnitNum();
    for (int i = 0; i < count; ++i)
        mRenderUnits[i]->_33 = lod_level_num;
}

// 0x7100c04b38
void ModelNW::syncResource() {
    nn::g3d::SkeletonObj* skeleton = mModelObj.GetSkeleton();
    skeleton->SetFlags(8);
    mBoneWorldMatrices = static_cast<BoneWorldMatrix*>(skeleton->GetWorldMatrices());
    mModelObj.SetUserPtr(this);
    mModelObj.SetBoneVisibilityCallback(&BoneVisibilityCallback);
    mModelObj.SetMaterialVisibilityCallback(&MaterialVisibilityCallback);
    mModelObj.SetTextureChangeCallback(&TextureChangeCallback);
}

// 0x7100c06594
void ModelNW::calcGPUSkinning_() {
    mModelObj.CalculateSkeleton(_168 & 3);
    mModelObj.CalculateShape(_168 & 3);
}

// 0x7100c04cd0
void ModelNW::setBoneLocalScale(const sead::Vector3f& scale, int bone_idx) {
    _200 |= 0x40;
    nn::g3d::SkeletonObj* skeleton = mModelObj.GetSkeleton();
    skeleton->SetFlags(2);
    nn::g3d::BoneLocalMatrix& matrix = *skeleton->GetLocalMatrix(bone_idx);
    matrix.mScale = scale;
    matrix.mFlags &= 0xf0ffffff;
}

// 0x7100c06be0
int ModelNW::getBoneNum() const {
    return mModelObj.GetSkeleton()->GetRes()->GetBoneCount();
}

// 0x7100c06db4
bool ModelNW::isBoneVisible(int bone_idx) const {
    return mModelObj.IsBoneVisible(bone_idx);
}

// 0x7100c07b5c
bool ModelNW::isMaterialVisible(int material_idx) const {
    return mModelObj.IsMatVisible(material_idx);
}

// 0x7100c06d60
// NON_MATCHING: same instructions, but clang schedules the new-bit shift after the old-bit test
// and picks different registers.
void ModelNW::setBoneVisible(int bone_idx, bool visible) {
    const bool old = mModelObj.SetBoneVisible(bone_idx, visible);
    auto callback = mModelObj.GetBoneVisibilityCallback();
    if (callback && old != visible)
        callback(&mModelObj, bone_idx);
}

// 0x7100c07b08
// NON_MATCHING: same instructions, but clang schedules the new-bit shift after the old-bit test
// and picks different registers.
void ModelNW::setMaterialVisible(int material_idx, bool visible) {
    const bool old = mModelObj.SetMatVisible(material_idx, visible);
    auto callback = mModelObj.GetMaterialVisibilityCallback();
    if (callback && old != visible)
        callback(&mModelObj, material_idx);
}

// 0x7100c04e54
sead::Matrix34f* ModelNW::getBoneWorldMatrixPtr(int bone_idx) const {
    _200 |= 4;
    return &mBoneWorldMatrices[bone_idx].mMatrix;
}

// 0x7100c070d0
bool ModelNW::getMaterialParamBool(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<int>(res->mShaderParams[param_idx].mDataOffset) != 0;
}

// 0x7100c071d4
int ModelNW::getMaterialParamInt(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<int>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c072cc
u32 ModelNW::getMaterialParamU32(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<u32>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c073c4
float ModelNW::getMaterialParamF32(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<float>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c074bc
const sead::Vector2f& ModelNW::getMaterialParamVector2f(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<sead::Vector2f>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c075c4
const sead::Vector3f& ModelNW::getMaterialParamVector3f(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<sead::Vector3f>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c076d4
const sead::Vector4f& ModelNW::getMaterialParamVector4f(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<sead::Vector4f>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c077ec
const sead::Color4f& ModelNW::getMaterialParamColor4f(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<sead::Color4f>(res->mShaderParams[param_idx].mDataOffset);
}

// 0x7100c078f4
sead::Color4f ModelNW::getMaterialParamColor3f(int material_idx, int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const sead::Vector3f& color =
        material->getParam<sead::Vector3f>(res->mShaderParams[param_idx].mDataOffset);
    return sead::Color4f(color.x, color.y, color.z, 1.0f);
}

// 0x7100c07a08
sead::Matrix34f* ModelNW::getMaterialParamEffectMatrixPtr(int material_idx,
                                                         int param_idx) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    return material->getParam<sead::Matrix34f*>(res->mShaderParams[param_idx].mDataOffset + 0x18);
}

// 0x7100c04e8c
void ModelNW::getMaterialParamTexSRT(int material_idx, int param_idx, sead::Vector2f* scale,
                                     float* rotate, sead::Vector2f* translate) const {
    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::MaterialParamTexSRT& value = material->getParam<nn::g3d::MaterialParamTexSRT>(
        res->mShaderParams[param_idx].mDataOffset);
    if (scale)
        *scale = value.mScale;
    if (rotate)
        *rotate = value.mRotate;
    if (translate)
        *translate = value.mTranslate;
}

// 0x7100c04fdc
// NON_MATCHING: the data pointer and the shader parameter offset are added in the other order;
// every other instruction agrees.
float ModelNW::getMaterialParamXluAlpha(int material_idx, int param_idx) const {
    const nn::g3d::ResMaterial* res = mModelObj.GetMaterial(material_idx)->GetResource();
    const auto* ex = static_cast<const G3dResMaterialEx*>(res->m_88);
    const s32 alpha_index = ex->getXluAlphaParamIndex();
    if (alpha_index == -1)
        return 1.0f;

    const nn::g3d::ResShaderParam& alpha = res->mShaderParams[alpha_index];
    const s32 count = s32(nn::g3d::ResShaderParam::GetSize(
                              nn::g3d::ResShaderParam::Type(alpha.mType)) >>
                          2);

    const nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const void* data = material->getParamData();
    const nn::g3d::ResMaterial* res2 = material->GetResource();
    const s32 index = count > param_idx ? param_idx : 0;
    const f32* values = static_cast<const f32*>(
        sead::PtrUtil::addOffset(data, res2->mShaderParams[alpha_index].mDataOffset));
    return values[index];
}

// 0x7100c0709c
sead::SafeString ModelNW::getMaterialParamName(int material_idx, int param_idx) const {
    const nn::g3d::ResMaterial* res = mModelObj.GetMaterial(material_idx)->GetResource();
    const nn::util::ResDic* dic = res->mShaderParamDic;
    const char* name = nullptr;
    if (dic)
        name = dic->GetKey(param_idx).data();
    return sead::SafeString(name);
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

// 0x7100c04b2c
void ModelNW::bindResource() {
    G3dResModelEx::getFromResModel(mModelObj.GetResource())->countUpReferenceCounter();
}

// 0x7100c04e70
int ModelNW::getBoneParentIndex(int bone_idx) const {
    return mModelObj.GetSkeleton()->GetRes()->GetBone(bone_idx)->GetParentIndex();
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
