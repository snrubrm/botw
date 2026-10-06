#include "gsys/gsysModel.h"
#include "gsys/gsysModelSceneEnv.h"
#include "gsys/gsysModelAnimation.h"
#include "gsys/gsysModelAutoAnimation.h"
#include "gsys/gsysModelNW.h"
#include <math/seadMathCalcCommon.h>
#include "gsys/gsysModelUnit.h"

namespace gsys {

// 0x7100bf79a4
int Model::getTotalBoneNum() const {
    int total = 0;
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        total += it->mModelUnit->getBoneNum();
    return total;
}

// 0x7100bf7a04
int Model::getMaxBoneNum() const {
    int max = 0;
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        max = sead::Mathi::max(max, it->mModelUnit->getBoneNum());
    return max;
}

// 0x7100bf7a68
int Model::getTotalMaterialNum() const {
    int total = 0;
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        total += it->mModelUnit->getMaterialNum();
    return total;
}

// 0x7100bf7ac8
int Model::getMaxMaterialNum() const {
    int max = 0;
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        max = sead::Mathi::max(max, it->mModelUnit->getMaterialNum());
    return max;
}

// 0x7100bf7b2c
void Model::setTotalBoneNum(int num, bool override) {
    if (override) {
        _a0 |= 8;
    } else {
        _a0 &= ~8;
        num = getTotalBoneNum();
    }
    _ac = num;
}

// 0x7100bf7cf0
void Model::x(bool on, int bit) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it) {
        if (on)
            it->mModelUnit->mVisibilityMask.setBit(bit);
        else
            it->mModelUnit->mVisibilityMask.resetBit(bit);
    }
}

// 0x7100bf7dd8
bool Model::isVisibilityBitOn(int bit) const {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it) {
        if (it->mModelUnit->mVisibilityMask.isOnBit(bit))
            return true;
    }
    return false;
}

// 0x7100bf7e34
void Model::setVisibilityMask(u16 mask) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->mVisibilityMask.setDirect(mask);
}

// 0x7100bf8b54
void Model::resetRenderToDepthShadow(int option) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->resetRenderOption(static_cast<ModelEnum::RenderOption>(option));
}

// 0x7100bf8ba8
void Model::sub_7100BF8BA8(int option) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->resetRenderViewOption(static_cast<ModelEnum::RenderViewOption>(option), -1);
}

// 0x7100bf8c04
void Model::resetRenderToDepthShadowOnly(int value) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->sub_7100C3E79C(value);
}

// 0x7100bf8c58
void Model::sub_7100BF8C58(bool on, int bit) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->enableRenderViewOption(static_cast<ModelEnum::RenderViewOption>(0), on, bit);
}

// 0x7100bf8cb8
void Model::sub_7100BF8CB8(bool on, int bit) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->enableRenderViewOption(static_cast<ModelEnum::RenderViewOption>(1), on, bit);
}

// 0x7100bf8d18
void Model::sub_7100BF8D18(bool on) {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
        it->mModelUnit->sub_7100C3E9B8(0x10, on);
}

// 0x7100bf7ea4
u16 Model::getVisibilityMaskAll() const {
    u16 mask = 0;
    for (auto& info : mUnitAccess)
        mask |= info.mModelUnit->mVisibilityMask;
    return mask;
}

// 0x7100bf7f18
u16 Model::getFlags14All() const {
    u16 flags = 0;
    for (auto& info : mUnitAccess)
        flags |= info.mModelUnit->_14;
    return flags;
}

// 0x7100bf7f8c
u32 Model::getMaxValue18() const {
    u32 max = 0;
    for (auto& info : mUnitAccess)
        max = sead::Mathu::max(max, info.mModelUnit->_18);
    return max;
}

// 0x7100bf7358
void Model::destroyAnimation_() {
    if (mAnimation) {
        mAnimation->finalize();
        ModelAnimation::destroy(mAnimation);
        mAnimation = nullptr;
    }
}

void Model::getBounding(sead::BoundSphere3f* bounding) const {
    const sead::BoundSphere3f* source = mBoundingOverrideMaybe;
    if (!source) {
        gatherBounding_();
        source = &mBounding;
    }
    *bounding = *source;
}

void Model::setAutoAnimationFrameRate(f32 frame_rate) {
    mAutoAnimationFrameRate = frame_rate;
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->mFrameRate = frame_rate;
        }
    }
}

void Model::forceAutoAnimationFrame(f32 frame) {
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->forceFrame(frame);
        }
    }
}

void Model::forceUpdateAutoAnimation() {
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->forceUpdate();
        }
    }
}

}  // namespace gsys
