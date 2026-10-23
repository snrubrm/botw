#include <gsys/gsysModelSceneFx.h>

#include <gsys/gsysModelSceneConfig.h>
#include <effect/aglFxCloud.h>
#include <effect/aglFxDecalDrawer.h>
#include <effect/aglFxNormalDrawer.h>
#include <effect/aglFxVolumeMask.h>

namespace gsys {

ModelSceneFx::CreateArg::CreateArg() : _0(1) {}

// 0x7100c2ee6c: the cloud exists, the Cloud feature is enabled and the cloud itself is active.
bool ModelSceneFx::isCloudEnabled() const {
    if (!mCloud)
        return false;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Cloud))
        return false;
    return mCloud->_460 != 0;
}

// 0x7100c2f35c: the decal drawer exists, the Decal feature is enabled and the drawer is active.
bool ModelSceneFx::isDecalEnabled() const {
    if (!mDecalDrawer)
        return false;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
        return false;
    return mDecalDrawer->_478 != 0;
}

// 0x7100c2fe38: the volume mask exists, its feature is enabled and the mask itself is active.
bool ModelSceneFx::isVolumeMaskEnabled() const {
    if (!mVolumeMask)
        return false;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::VolumeMask))
        return false;
    return mVolumeMask->_4e0 != 0;
}

// 0x7100c30188
bool ModelSceneFx::isCloudDrawReduceBufffer() const {
    if (!mCloud)
        return false;
    return mCloud->_480 != 0;
}

// 0x7100c301a8
bool ModelSceneFx::isCloudDrawAllocBufffer() const {
    if (!mCloud)
        return false;
    return mCloud->_618 != 0;
}

// 0x7100c2fb74
void ModelSceneFx::releaseWaterNormalModify(int index) const {
    mNormalDrawer->release(index);
}

// 0x7100c2fe6c: the mask exists, its feature is enabled and it is active.
void ModelSceneFx::releaseVolumeMaskTexture(int index) const {
    if (!mVolumeMask)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::VolumeMask))
        return;
    if (!mVolumeMask->_4e0)
        return;
    mVolumeMask->releaseMaskTexture(index);
}

}  // namespace gsys
