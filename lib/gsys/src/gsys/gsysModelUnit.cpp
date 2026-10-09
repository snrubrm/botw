#include "gsys/gsysModelUnit.h"

namespace gsys {

void ModelUnit::sub_7100C44D58(const sead::SafeString& name) { mName = name; }

// 0x7100c3e2d0
void ModelUnit::enableRenderViewOption(int material_idx, ModelEnum::RenderViewOption option,
                                       bool enable, int view) {
    const u32 mask = 1 << int(option);
    if (view != -1) {
        ViewOption& record = mViewOptions[material_idx * getViewNum() + view];
        if (((record.flags & mask) != 0) == enable)
            return;
        record.flags = enable ? record.flags | mask : record.flags & ~mask;
        mFlags.set(Flag::Changed);
        mMaterialInfo[material_idx].flags.setBit(1);
        return;
    }

    int i = 0;
    bool changed = false;
    for (; i < getViewNum(); ++i) {
        ViewOption& record = mViewOptions[material_idx * getViewNum() + i];
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
            for (int v = 0; v < getViewNum(); ++v)
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

}  // namespace gsys
