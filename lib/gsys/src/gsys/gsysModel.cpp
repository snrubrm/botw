#include "gsys/gsysModel.h"
#include "gsys/gsysModelSceneEnv.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModelAnimation.h"
#include "gsys/gsysModelAutoAnimation.h"
#include "gsys/gsysModelNW.h"
#include <math/seadMathCalcCommon.h>
#include "gsys/gsysModelUnit.h"
#include <prim/seadScopedLock.h>
#include "gsys/gsysModelScene.h"

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

// 0x7100bf7bb4
BoneAccessKey Model::searchBone(const sead::SafeString& name) const {
    BoneAccessKey key;
    int i = 0;
    for (auto& info : mUnitAccess) {
        const int bone_index = info.mModelUnit->searchBoneIndex(name);
        if (bone_index != -1) {
            key.model_unit_index = i;
            key.bone_index = bone_index;
            return key;
        }
        ++i;
    }
    return key;
}

// 0x7100bf7c30
void Model::setBoneLocalMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix,
                               const sead::Vector3f& scale) {
    mUnitAccess(key.model_unit_index)->mModelUnit->setBoneLocalMatrix(matrix, scale, key.bone_index);
}

// 0x7100bf7c5c
void Model::setBoneLocalRTMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix) {
    mUnitAccess(key.model_unit_index)->mModelUnit->setBoneLocalRTMatrix(matrix, key.bone_index);
}

// 0x7100bf7c84
void Model::setBoneWorldMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix) {
    mUnitAccess(key.model_unit_index)->mModelUnit->setBoneWorldMatrix(matrix, key.bone_index);
}

// 0x7100bf7cac
void Model::clearBoneLocalMatrix() const {
    for (auto& info : mUnitAccess)
        info.mModelUnit->clearBoneLocalMatrix();
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

// 0x7100bf82e8
MaterialAccessKey Model::searchMaterial(const sead::SafeString& name) const {
    MaterialAccessKey key;
    int i = 0;
    for (auto& info : mUnitAccess) {
        const int material_index = info.mModelUnit->searchMaterialIndex(name);
        if (material_index != -1) {
            key.model_unit_index = i;
            key.material_index = material_index;
            return key;
        }
        ++i;
    }
    return key;
}

// 0x7100bf8364
void Model::setMaterialVisibleAll(bool visible) {
    for (auto& info : mUnitAccess)
        info.mModelUnit->setMaterialVisibleAll(visible);
}

// 0x7100bf99b0
void Model::requestUpdate(u32 flags) {
    _a3 = flags;
    _a1 |= 4;
}

// 0x7100bf95bc
void Model::updateBounding() {
    for (auto& info : _48)
        info.mModelUnit->calcBounding();
}

// 0x7100bf6d94
void Model::bind(ModelScene* scene) {
    if (mScene && mScene != scene)
        mScene->unbind_(this);
    mScene = scene;
    if (scene) {
        scene->bind_(this);
        for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it)
            it->mModelUnit->bind(mScene);
    }
}

// 0x7100bf6e20
void Model::clearModelAccesssHandle() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto it = mHandleList.robustBegin(); it != mHandleList.robustEnd(); ++it)
        it->remove();
}

// 0x7100bf76d0
void Model::updateModelAccesssHandle_() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& handle : mHandleList)
        handle.search();
}

// 0x7100bf7748
void Model::add_(IModelAccesssHandle* handle) const {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mHandleList.pushBack(handle);
}

// 0x7100bf779c
void Model::remove_(IModelAccesssHandle* handle) const {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mHandleList.erase(handle);
}

// 0x7100bf8e24
void Model::applyAnimationTo(Model* target, u32 flags) {
    if (mAnimation) {
        if (target->mUpdateHook)
            target->mUpdateHook->m0(target);
        if (flags & 1)
            mAnimation->applySkeletalAnm(target);
        if (flags & 2)
            mAnimation->sub_7100BFDDCC(target);
    }
}

// 0x7100bf8f48
void Model::safeApplyAnimation(u32 flags) {
    if (mAnimation) {
        if (mUpdateHook)
            mUpdateHook->m0(this);
        if (flags & 1)
            mAnimation->applySkeletalAnm(this);
        if (flags & 2)
            mAnimation->sub_7100BFDDCC(this);
    }
}

// 0x7100bf8e9c
void Model::updateWorldMatrix() {
    if (auto* hook = mUpdateHook) {
        hook->m1(this);
        for (auto& info : _48)
            updateWorldMatrixModelUnit_(&info);
        hook->m2(this);
    } else {
        for (auto& info : _48)
            updateWorldMatrixModelUnit_(&info);
    }
    _a0 &= ~1;
}

// 0x7100bf8fb0
void Model::safeUpdateWorldMatrix() {
    if (auto* hook = mUpdateHook) {
        hook->m1(this);
        for (auto& info : _48)
            updateWorldMatrixModelUnit_(&info);
        hook->m2(this);
    } else {
        for (auto& info : _48)
            updateWorldMatrixModelUnit_(&info);
    }
    _a0 &= ~1;
}

// 0x7100bf905c
void Model::updateWorldMatrix(int unit_idx) {
    updateWorldMatrixModelUnit_(_48.at(unit_idx));
}

// 0x7100bf8738
void Model::sub_7100BF8738() {
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it) {
        for (int i = 0, n = it->mModelUnit->getMaterialNum(); i < n; ++i)
            it->mModelUnit->clearMaterialParameter(i);
    }
    if (mUpdateHook)
        mUpdateHook->m3(this);
}

// NON_MATCHING: the stores of reference._1e and reference._8 come out in the other order (scheduling)
// 0x7100bf8d70
void Model::sub_7100BF8D70(int unit_idx) {
    ModelInfo& reference = mUnitPool[unit_idx];
    reference._1e &= ~8;
    reference._8 = nullptr;
    reference.mModelUnit->setReferenceLod(*reference.mModelUnit);
    ModelInfo* last = &reference;
    for (auto it = mUnitPool.begin(), end = mUnitPool.begin(getUsedUnitNum()); it != end; ++it) {
        if (&*it == &reference)
            continue;
        it->_1e |= 8;
        it->_8 = nullptr;
        it->mModelUnit->setReferenceLod(*reference.mModelUnit);
        last->_8 = &*it;
        last = &*it;
    }
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
        it->mModelUnit->enableRenderOption(static_cast<ModelEnum::RenderOption>(0x10), on);
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

// 0x7100bf9bd8
bool Model::hasRigObj(int unit_idx, IModelRigObj* obj) const {
    return mUnitAccess.unsafeAt(unit_idx)->mRigObjs.indexOf(obj) != -1;
}

// 0x7100bf9c08
void Model::pushBack(int unit_idx, IModelRigObj* obj) {
    mUnitAccess.at(unit_idx)->mRigObjs.pushBack(obj);
}

// 0x7100bf9c58
bool Model::erase(int unit_idx, IModelRigObj* obj) {
    mUnitAccess.at(unit_idx)->mRigObjs.erase(obj);
    return true;
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
