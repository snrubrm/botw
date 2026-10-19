#include "gsys/gsysModelUnit.h"

namespace gsys {

void ModelUnit::sub_7100C44D58(const sead::SafeString& name) { mName = name; }

// 0x7100c3e2d0
void ModelUnit::enableRenderViewOption(int material_idx, ModelEnum::RenderViewOption option,
                                       bool enable, int view) {
    const u32 mask = 1 << int(option);
    if (view != -1) {
        ViewOption& record = mViewOptions[material_idx * getShapeNum() + view];
        if (((record.flags & mask) != 0) == enable)
            return;
        record.flags = enable ? record.flags | mask : record.flags & ~mask;
        mFlags.set(Flag::Changed);
        mMaterialInfo[material_idx].flags.setBit(1);
        return;
    }

    int i = 0;
    bool changed = false;
    for (; i < getShapeNum(); ++i) {
        ViewOption& record = mViewOptions[material_idx * getShapeNum() + i];
        if (enable) {
            if (!record.flags.isOn(mask)) {
                record.flags.set(mask);
                changed = true;
            }
        } else {
            if (record.flags.isOn(mask)) {
                record.flags.reset(mask);
                changed = true;
            }
        }
    }
    if (changed) {
        mFlags.set(Flag::Changed);
        mMaterialInfo[material_idx].flags.setBit(1);
    }
}

// 0x7100c3e5a0
void ModelUnit::setMaterialVisibleAll(bool visible) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i)
        setMaterialVisible(i, visible);
}

// 0x7100c3e60c
void ModelUnit::setShaderAssignVariation(ModelEnum::ShaderAssignType assign_type, int variation) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i)
        setMaterialShaderAssignVariation(i, assign_type, variation);
}

// 0x7100c3e684
void ModelUnit::copyBoneLocalMatrixTo(ModelUnit* target) const {
    for (int i = 0, n = getBoneNum(); i < n; ++i) {
        sead::Matrix34f matrix;
        sead::Vector3f scale;
        getBoneLocalMatrix(&matrix, &scale, i);
        target->setBoneLocalMatrix(matrix, scale, i);
    }
}

// 0x7100c3e714
void ModelUnit::copyBoneWorldMatrixTo(ModelUnit* target) const {
    for (int i = 0, n = getBoneNum(); i < n; ++i) {
        sead::Matrix34f matrix;
        getBoneWorldMatrix(&matrix, i);
        target->setBoneWorldMatrix(matrix, i);
    }
}

// 0x7100c3e82c
void ModelUnit::enableReverseCulling(bool enable) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i)
        enableReverseCulling(i, enable);
}

// 0x7100c3f4c4
void ModelUnit::updateQueueInfo() {
    if (mFlags.isOn(Flag::Changed)) {
        updateQueueInfo_();
        mFlags.reset(Flag::Changed);
    }
}

// 0x7100c3e79c
void ModelUnit::sub_7100C3E79C(int value) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i)
        mMaterialInfo[i]._4 = value;
}

// 0x7100c3e898
void ModelUnit::sub_7100C3E898(int bit, bool enable) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i) {
        if (enable)
            mMaterialInfo[i]._8.setBit(bit);
        else
            mMaterialInfo[i]._8.resetBit(bit);
        mFlags.set(Flag::Changed);
        mMaterialInfo[i].flags.setBit(1);
    }
}

// 0x7100c3e9b8
void ModelUnit::enableRenderOption(ModelEnum::RenderOption option, bool enable) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i) {
        if (enable)
            mMaterialInfo[i].renderOptions |= 1 << int(option);
        else
            mMaterialInfo[i].renderOptions &= ~(1 << int(option));
        mFlags.set(Flag::Changed);
        mMaterialInfo[i].flags.setBit(1);
    }
}

// 0x7100c3ea8c
void ModelUnit::resetRenderOption(ModelEnum::RenderOption option) {
    const u32 mask = 1 << int(option);
    for (int i = 0, n = getMaterialNum(); i < n; ++i) {
        const bool enabled = isDefaultRenderOptionEnabled(i, option);
        mMaterialInfo[i].renderOptions =
            enabled ? mMaterialInfo[i].renderOptions | mask : mMaterialInfo[i].renderOptions & ~mask;
        mFlags.set(Flag::Changed);
        mMaterialInfo[i].flags.setBit(1);
    }
}

// 0x7100c3eb54
void ModelUnit::enableRenderViewOption(ModelEnum::RenderViewOption option, bool enable, int view) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i)
        enableRenderViewOption(i, option, enable, view);
}

// 0x7100c3ebd0
void ModelUnit::resetRenderViewOption(ModelEnum::RenderViewOption option, int view) {
    const int material_num = getMaterialNum();
    if (view != -1) {
        for (int i = 0; i < material_num; ++i)
            enableRenderViewOption(i, option, isDefaultRenderViewOptionEnabled(i, option, view),
                                   view);
    } else {
        for (int i = 0; i < material_num; ++i) {
            for (int v = 0; v < getShapeNum(); ++v)
                enableRenderViewOption(i, option,
                                       isDefaultRenderViewOptionEnabled(i, option, v), v);
        }
    }
}

// 0x7100c3ecf0
void ModelUnit::sub_7100C3ECF0(int bit, bool enable) {
    for (int i = 0, n = getMaterialNum(); i < n; ++i) {
        if (enable)
            mMaterialInfo[i].flags.setBit(bit + 5);
        else
            mMaterialInfo[i].flags.resetBit(bit + 5);
        mFlags.set(Flag::Changed);
        mMaterialInfo[i].flags.setBit(1);
    }
}

// 0x7100c3ee8c
void ModelUnit::sub_7100C3EE8C(u8 depth_shadow_cascade) {
    mDepthShadowCascade = depth_shadow_cascade;
    for (int i = 0, n = getMaterialNum(); i < n; ++i) {
        mFlags.set(Flag::Changed);
        mMaterialInfo[i].flags.setBit(1);
    }
}

// 0x7100c3e974
void ModelUnit::calcBoundAABB(sead::BoundBox3f* aabb, bool) const {
    const f32 radius = _50->getRadius();
    const sead::Vector3f extent(radius, radius, radius);
    aabb->setMin(_50->getCenter() - extent);
    aabb->setMax(_50->getCenter() + extent);
}

// 0x7100c146f8
void* ModelUnit::createSubMeshRangeBuffer(sead::Heap* heap) const {
    return nullptr;
}

// 0x7100c146c0
void ModelUnit::getMaterialParamTexSRT(int, int, sead::Vector2f*, float*, sead::Vector2f*) const {}

// 0x7100c146c4
void ModelUnit::setMaterialParamTexSRT(int, int, const sead::Vector2f&, float,
                                       const sead::Vector2f&) {}

// 0x7100c14700
void ModelUnit::setSubMeshRangeBuffer(int, void*) {}

// 0x7100c14704
void ModelUnit::setSubMeshRangeBufferVisible(int, int, const bool*) {}

// 0x7100c14718
bool ModelUnit::isDefaultRenderOptionEnabled(int, ModelEnum::RenderOption) const {
    return false;
}

// 0x7100c14720
bool ModelUnit::isDefaultRenderViewOptionEnabled(int, ModelEnum::RenderViewOption, int) const {
    return false;
}

// 0x7100c14738
bool ModelUnit::isReverseCullingEnabled(int) const {
    return false;
}

// The bone and material accessors below are the ModelUnit defaults; the concrete
// units (ModelUnitNW and the procedural units) override them.

// 0x7100c14574
int ModelUnit::getBoneNum() const {
    return 1;
}

// 0x7100c1457c
int ModelUnit::searchBoneIndex(const sead::SafeString&) const {
    return -1;
}

// 0x7100c145a4
void ModelUnit::setBoneLocalMatrix(const sead::Matrix34f&, const sead::Vector3f&, int) {}

// 0x7100c145a8
void ModelUnit::setBoneLocalRTMatrix(const sead::Matrix34f&, int) {}

// 0x7100c145ac
void ModelUnit::setBoneLocalScale(const sead::Vector3f&, int) {}

// 0x7100c145b0
void ModelUnit::getBoneLocalMatrix(sead::Matrix34f*, sead::Vector3f*, int) const {}

// 0x7100c145b4
void ModelUnit::setBoneWorldMatrix(const sead::Matrix34f&, int) {}

// 0x7100c145b8
void ModelUnit::getBoneWorldMatrix(sead::Matrix34f*, int) const {}

// 0x7100c145bc
sead::Matrix34f* ModelUnit::getBoneWorldMatrixPtr(int) const {
    return nullptr;
}

// 0x7100c145c4
void ModelUnit::safeGetBoneWorldMatrix(sead::Matrix34f*, int) const {}

// 0x7100c145c8
void ModelUnit::setBoneVisible(int, bool) {}

// 0x7100c145cc
bool ModelUnit::isBoneVisible(int) const {
    return true;
}

// 0x7100c145d4
int ModelUnit::getBoneParentIndex(int) const {
    return -1;
}

// 0x7100c145dc
void ModelUnit::clearBoneLocalMatrix() {}

// 0x7100c145e8
int ModelUnit::searchMaterialIndex(const sead::SafeString&) const {
    return -1;
}

// 0x7100c14610
int ModelUnit::searchMaterialParamIndex(int, const sead::SafeString&) const {
    return -1;
}

// 0x7100c14638
bool ModelUnit::getMaterialParamBool(int, int) const {
    return false;
}

// 0x7100c14640
void ModelUnit::setMaterialParamBool(int, int, bool) {}

// 0x7100c14644
int ModelUnit::getMaterialParamInt(int, int) const {
    return 0;
}

// 0x7100c1464c
void ModelUnit::setMaterialParamInt(int, int, int) {}

// 0x7100c14650
u32 ModelUnit::getMaterialParamU32(int, int) const {
    return 0;
}

// 0x7100c14658
void ModelUnit::setMaterialParamU32(int, int, u32) {}

// 0x7100c1465c
float ModelUnit::getMaterialParamF32(int, int) const {
    return 0.0f;
}

// 0x7100c14664
void ModelUnit::setMaterialParamF32(int, int, float) {}

// 0x7100c14674
void ModelUnit::setMaterialParamVector2f(int, int, const sead::Vector2f&) {}

// 0x7100c14684
void ModelUnit::setMaterialParamVector3f(int, int, const sead::Vector3f&) {}

// 0x7100c14694
void ModelUnit::setMaterialParamVector4f(int, int, const sead::Vector4f&) {}

// 0x7100c146a4
void ModelUnit::setMaterialParamColor4f(int, int, const sead::Color4f&) {}

// 0x7100c146bc
void ModelUnit::setMaterialParamColor3f(int, int, const sead::Color4f&) {}

// 0x7100c146c8
sead::Matrix34f* ModelUnit::getMaterialParamEffectMatrixPtr(int, int) const {
    return nullptr;
}

// 0x7100c146d0
void ModelUnit::setMaterialParamEffectMatrixPtr(int, int, sead::Matrix34f*) {}

// 0x7100c146d4
float ModelUnit::getMaterialParamXluAlpha(int, int) const {
    return 1.0f;
}

// 0x7100c146e4
void ModelUnit::clearMaterialParameter(int) {}

// 0x7100c146e8
void ModelUnit::clearTexture(int) {}

// 0x7100c146ec
void ModelUnit::setMaterialShaderAssignVariation(int, ModelEnum::ShaderAssignType, int) {}

// 0x7100c14708
int ModelUnit::countPolygonNum() const {
    return 1;
}

// 0x7100c14734
void ModelUnit::enableReverseCulling(int, bool) {}

// 0x7100c14740
void ModelUnit::setLodLevelNum(int lod_level_num) {
    mNumLods = lod_level_num;
}

// 0x7100c14750
void ModelUnit::calcBounding() {}

// 0x7100c14754
void ModelUnit::bind(const ModelScene*) {}

// 0x7100c14758
void ModelUnit::bindResource() {}

// 0x7100c1475c
void ModelUnit::syncResource() {}

// 0x7100c14760
void ModelUnit::unbindResource() {}

// 0x7100c14764
void ModelUnit::calcWorld(const sead::Matrix34f&, const sead::Vector3f&) {}

// 0x7100c14768
void ModelUnit::postCalcWorld(const ModelScene*, u32, u32, const ModelViewData*, int) {}

// 0x7100c1476c
void ModelUnit::calcBeforeDraw(ModelScene*, const ModelViewData*, int) {}

// 0x7100c14770
void ModelUnit::forceCalcDrawSetup() {}

// 0x7100c44e4c
void ModelUnit::setMaterialVisible(int, bool) {}

// 0x7100c44e50
bool ModelUnit::isMaterialVisible(int) const {
    return true;
}

// 0x7100c44e2c / 0x7100c14584 / 0x7100c145f0 / 0x7100c14618
sead::SafeString ModelUnit::getName() const {
    return sead::SafeStringBase<char>::cEmptyString;
}

sead::SafeString ModelUnit::getBoneName(int) const {
    return sead::SafeStringBase<char>::cEmptyString;
}

sead::SafeString ModelUnit::getMaterialName(int) const {
    return sead::SafeStringBase<char>::cEmptyString;
}

sead::SafeString ModelUnit::getMaterialParamName(int, int) const {
    return sead::SafeStringBase<char>::cEmptyString;
}

// 0x7100c14668 / 0x7100c14678 / 0x7100c14688 / 0x7100c14698
const sead::Vector2f& ModelUnit::getMaterialParamVector2f(int, int) const {
    return sead::Vector2f::zero;
}

const sead::Vector3f& ModelUnit::getMaterialParamVector3f(int, int) const {
    return sead::Vector3f::zero;
}

const sead::Vector4f& ModelUnit::getMaterialParamVector4f(int, int) const {
    return sead::Vector4f::zero;
}

const sead::Color4f& ModelUnit::getMaterialParamColor4f(int, int) const {
    return sead::Color4f::cBlack;
}

}  // namespace gsys
