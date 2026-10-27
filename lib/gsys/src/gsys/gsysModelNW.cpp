#include "gsys/gsysModelNW.h"
#include "gsys/gsysModelRenderUnitNW.h"
#include "gsys/gsysModelDynamicEnvInfo.h"
#include "gsys/gsysG3dResModelEx.h"
#include "gsys/gsysG3dResMaterialEx.h"
#include "gsys/gsysModelResourceMgr.h"
#include <g3d/aglNW4FToNN.h>
#include <heap/seadHeapMgr.h>
#include <cstring>
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

// 0x7100c063fc
void ModelNW::forceCalcDrawSetup() {
    calcBounding_();
    calcGPUSkinning_();
    mModelObj.CalculateMaterial(_168 & 3);
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
        static_cast<const void*>(static_cast<const u8*>(data) +
                                 res2->mShaderParams[alpha_index].mDataOffset));
    return values[index];
}

// 0x7100c07200
void ModelNW::setMaterialParamInt(int material_idx, int param_idx, int value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<int>(param->mDataOffset, value);
}

// 0x7100c07104
void ModelNW::setMaterialParamBool(int material_idx, int param_idx, bool value) {
    const u32 stored = value;
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<u32>(param->mDataOffset, stored);
}

// 0x7100c072f8
void ModelNW::setMaterialParamU32(int material_idx, int param_idx, u32 value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<u32>(param->mDataOffset, value);
}

// 0x7100c073f0
void ModelNW::setMaterialParamF32(int material_idx, int param_idx, float value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<float>(param->mDataOffset, value);
}

// 0x7100c074e8
void ModelNW::setMaterialParamVector2f(int material_idx, int param_idx,
                                       const sead::Vector2f& value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<sead::Vector2f>(param->mDataOffset, value);
}

// 0x7100c075f0
void ModelNW::setMaterialParamVector3f(int material_idx, int param_idx,
                                       const sead::Vector3f& value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<sead::Vector3f>(param->mDataOffset, value);
}

// 0x7100c07700
void ModelNW::setMaterialParamVector4f(int material_idx, int param_idx,
                                       const sead::Vector4f& value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<sead::Vector4f>(param->mDataOffset, value);
}

// 0x7100c07818
void ModelNW::setMaterialParamColor4f(int material_idx, int param_idx,
                                      const sead::Color4f& value) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<sead::Color4f>(param->mDataOffset, value);
}

// 0x7100c0792c
void ModelNW::setMaterialParamColor3f(int material_idx, int param_idx,
                                      const sead::Color4f& value) {
    const sead::Vector3f color(value.r, value.g, value.b);
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<sead::Vector3f>(param->mDataOffset, color);
}

// 0x7100c07a38
void ModelNW::setMaterialParamEffectMatrixPtr(int material_idx, int param_idx,
                                              sead::Matrix34f* matrix) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    const u16 offset = param->mDataOffset;
    u8* data = static_cast<u8*>(material->m_UserData) + offset;
    *static_cast<sead::Matrix34f**>(static_cast<void*>(data + 0x18)) = matrix;
}

// 0x7100c04eec
void ModelNW::setMaterialParamTexSRT(int material_idx, int param_idx,
                                     const sead::Vector2f& scale, float rotate,
                                     const sead::Vector2f& translate) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const nn::g3d::ResMaterial* res = material->GetResource();
    const nn::g3d::ResShaderParam* param = &res->mShaderParams[param_idx];
    if ((param->mFlags & 0x80000000) == 0)
        material->markParamDirty(param_idx);

    const u16 dependent = param->mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    const u16 offset = param->mDataOffset;
    u8* data = static_cast<u8*>(material->m_UserData) + offset;
    auto* value = static_cast<nn::g3d::MaterialParamTexSRT*>(static_cast<void*>(data));
    value->mScale = scale;
    value->mRotate = rotate;
    value->mTranslate = translate;
}

// 0x7100c05074
// NON_MATCHING: the body is complete; clang keeps the alpha-parameter offset in a second
// register and folds the final store address, so the call-preserved set and two instructions
// differ from the original.
bool ModelNW::setMaterialParamXluAlpha(int material_idx, int param_idx, float xlu_alpha) {
    const nn::g3d::ResMaterial* res = mModelObj.GetMaterial(material_idx)->GetResource();
    const auto* ex = static_cast<const G3dResMaterialEx*>(res->m_88);
    const s32 alpha_index = ex->getXluAlphaParamIndex();
    if (alpha_index == -1)
        return false;

    const nn::g3d::ResShaderParam& alpha = res->mShaderParams[alpha_index];
    const size_t size =
        nn::g3d::ResShaderParam::GetSize(nn::g3d::ResShaderParam::Type(alpha.mType));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    const void* data = material->getParamData();
    const nn::g3d::ResMaterial* res2 = material->GetResource();
    const s32 index = param_idx < (size >> 2) ? param_idx : 0;
    const u16 offset = res2->mShaderParams[alpha_index].mDataOffset;
    const f32* values = static_cast<const f32*>(
        static_cast<const void*>(static_cast<const u8*>(data) + offset));
    if (values[index] == xlu_alpha)
        return false;

    if ((alpha.mFlags & 0x80000000) == 0)
        material->markParamDirty(alpha_index);

    const u16 dependent = alpha.mDependentIndex;
    if ((material->GetResource()->mShaderParams[dependent].mFlags & 0x80000000) == 0)
        material->markParamDirty(dependent);

    material->setParam<float>(offset + index * sizeof(f32), xlu_alpha);

    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));
    return true;
}

// 0x7100c04b7c
void ModelNW::unbindResource() {
    if (ModelResourceMgr::instance()->isExist(mModelObj.GetResource()))
        static_cast<G3dResModelEx*>(mModelObj.GetResource()->pExtension)
            ->countDownReferenceCounter();
}

// 0x7100c05258
void ModelNW::setMaterialShaderAssignVariation(int material_idx,
                                               ModelEnum::ShaderAssignType assign_type,
                                               int variation) {
    const int num = getModelRenderUnitNum();
    for (int i = 0; i < num; ++i) {
        ModelRenderUnitNW* unit = mRenderUnits[i];
        if (unit->getMaterialIndex() == material_idx)
            unit->setShaderVariation(int(assign_type), u32(variation));
    }
}

// 0x7100c052f0
void ModelNW::enableReverseCulling(int index, bool enable) {
    const int num = getModelRenderUnitNum();
    if (num < 1)
        return;
    if (enable) {
        for (int i = 0; i < num; ++i) {
            ModelRenderUnitNW* unit = mRenderUnits[i];
            if (unit->getMaterialIndex() == index)
                unit->setPolygonCtrl(unit->mPolygonCtrl | 8);
        }
    } else {
        for (int i = 0; i < num; ++i) {
            ModelRenderUnitNW* unit = mRenderUnits[i];
            if (unit->getMaterialIndex() == index)
                unit->setPolygonCtrl(unit->mPolygonCtrl & ~8);
        }
    }
}

// 0x7100c053a8
bool ModelNW::isReverseCullingEnabled(int index) const {
    bool enabled = false;
    const int num = getModelRenderUnitNum();
    for (int i = 0; i < num; ++i) {
        const ModelRenderUnitNW* unit = mRenderUnits[i];
        if (unit->getMaterialIndex() == index) {
            enabled = (unit->mPolygonCtrl & 8) != 0;
            break;
        }
    }
    return enabled;
}

// 0x7100c0445c
void* ModelNW::createSubMeshRangeBuffer(sead::Heap* heap) const {
    int num = 0;
    for (int i = 0; i < getModelRenderUnitNum(); ++i) {
        const nn::g3d::ResShape* shape = mModelObj.GetShape(i)->GetResource();
        num += getSubMeshRangeNum(shape->GetMeshCount(), shape->GetMesh(0)->GetSubMeshCount());
    }
    return new (heap, 8) u8[num * sizeof(SubMeshRange)]();
}

// 0x7100c04648
void ModelNW::setSubMeshRangeBuffer(int index, void* buffer) {
    SubMeshRange* range = static_cast<SubMeshRange*>(buffer);
    if (range) {
        for (int i = 0; i < getModelRenderUnitNum(); ++i) {
            ModelRenderUnitNW* unit = mRenderUnits[i];
            if (unit->mShapeRecords)
                unit->mShapeRecords[index]._8 = range;
            const nn::g3d::ResShape* shape = mModelObj.GetShape(i)->GetResource();
            range += getSubMeshRangeNum(shape->GetMeshCount(),
                                        shape->GetMesh(0)->GetSubMeshCount());
        }
    } else {
        for (int i = 0; i < getModelRenderUnitNum(); ++i) {
            ModelRenderUnitNW* unit = mRenderUnits[i];
            if (unit->mShapeRecords)
                unit->mShapeRecords[index]._8 = nullptr;
        }
    }
}

// 0x7100c04528
void ModelNW::setSubMeshRangeBufferVisible(int index, int shape, const bool* visible) {
    ModelRenderUnitNW* unit = mRenderUnits[shape];
    if (!unit->mShapeRecords)
        return;
    u16* range = static_cast<u16*>(unit->mShapeRecords[index]._8);
    if (!range)
        return;
    range[0] = 0;
    range[1] = 0;
    const int num = getShapeSubMeshNum(shape);
    if (num >= 1) {
        for (int i = 0; i < num; ++i) {
            if (!visible || visible[i]) {
                if (range[1] == 0)
                    range[0] = i;
                ++range[1];
            } else if (range[1] != 0 || range[0] != 0) {
                range += 3;
                range[0] = 0;
                range[1] = 0;
            }
            range[2] = 0;
        }
    }
    if (range[1] != 0 || range[0] != 0) {
        range += 3;
        range[0] = 0;
        range[1] = 0;
    }
}

// 0x7100c054bc
int ModelNW::countPolygonNum() const {
    int count = 0;
    for (int i = 0; i < getModelRenderUnitNum(); ++i) {
        const nn::g3d::ResMesh* mesh = mModelObj.GetShape(i)->GetResource()->GetMesh(0);
        count += mesh->mIndexCount / 3;
    }
    return count;
}

// NON_MATCHING: the body and size agree, but clang narrows the clear mask to the stored byte
// (eor #0xff) where the original complements the full word (mvn).
// 0x7100c0678c
void ModelNW::setUserUniformBlock(int index, agl::UniformBlock* block) {
    if (_70[index] == block)
        return;
    _70[index] = block;
    const int num = getModelRenderUnitNum();
    const u32 bit = 1u << index;
    for (int i = 0; i < num; ++i) {
        ModelRenderUnitNW* unit = mRenderUnits[i];
        if (block)
            unit->_232 |= bit;
        else
            unit->_232 &= ~bit;
    }
}

// NON_MATCHING: the body agrees, but clang keeps the address of _200 in a register (one extra
// add) and folds the clear mask to a 32-bit immediate.
// NON_MATCHING: the body agrees, but clang sinks the view-option record load into the
// non-default arm; the original computes it before testing the option.
// 0x7100c066ec
bool ModelNW::isDefaultRenderViewOptionEnabled(int material_idx,
                                               ModelEnum::RenderViewOption option,
                                               int view) const {
    const nn::g3d::ResMaterial* res = mModelObj.GetMaterial(material_idx)->GetResource();
    const auto* ex = static_cast<const G3dResMaterialEx*>(res->m_88);
    bool enabled = (mViewOptions[getShapeNum() * material_idx + view].flags &
                    (1 << int(option))) != 0;
    if (int(option) == 0 || int(option) == 1)
        enabled = (ex->mRenderState.mRenderOptionFlags & (1 << int(option))) != 0;
    return enabled;
}

// 0x7100c03e8c
void ModelNW::setCallbackBoneIndex(int bone_idx) {
    nn::g3d::SkeletonObj* skeleton = mModelObj.GetSkeleton();
    if (bone_idx != -1 && mBoneCallback) {
        skeleton->setCalculateWorldCallback(this);
        _200 |= 0x50;
    } else {
        skeleton->setCalculateWorldCallback(nullptr);
        _200 &= ~0x10;
    }
    skeleton->setCallbackBoneIndex(bone_idx);
}

// 0x7100c051e4
void ModelNW::clearMaterialParameter(int material_idx) {
    const u8 buffer_mask = u8((0x10 << mBufferNum) + 0xf0);
    _201 = u8(buffer_mask | (_201 & 0xf));

    nn::g3d::MaterialObj* material = mModelObj.GetMaterial(material_idx);
    material->ResetDirtyFlags();

    const nn::g3d::ResMaterial* res = material->GetResource();
    memcpy(material->m_UserData, res->mDefaultParamData, res->mParamDataSize);
    material->InitializeDependPointer();
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
