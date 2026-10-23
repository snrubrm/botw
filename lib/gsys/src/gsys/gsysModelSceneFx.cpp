#include <gsys/gsysModelSceneFx.h>

#include <gsys/gsysModelSceneConfig.h>
#include <gsys/gsysModelSceneContext.h>
#include <common/aglRenderBuffer.h>
#include <effect/aglFxCloud.h>
#include <effect/aglFxDecalAoMgr.h>
#include <effect/aglFxDecalDrawer.h>
#include <effect/aglFxNormalDrawer.h>
#include <effect/aglFxOfxBase.h>
#include <effect/aglFxRadialBlur.h>
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

// 0x7100c2f57c: the decal AO pass draws after the decal drawer when both are enabled.
void ModelSceneFx::drawDecalBG(agl::DrawContext* context, ModelSceneContext* scene_context) const {
    if (!mDecalDrawer)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
        return;
    if (!mDecalDrawer->_478)
        return;
    if (!mDecalAoMgr)
        return;
    if (!_8->useDecalAo())
        return;
    mDecalAoMgr->updateDecal_draw(context);
}

// 0x7100c2f390: the scene's radial blur follows the first view's matrices.
void ModelSceneFx::calcView(const ModelSceneContext& context) {
    if (!mRadialBlur)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::RadialBlur))
        return;
    mRadialBlur->calcView(context._8, context.mViews[0].mView, context.mViews[0].mProjection);
}

// 0x7100c2f3c0: the occluded effects follow the current view's matrices and factors.
void ModelSceneFx::calcViewOccludedEffect(const ModelSceneContext& context) {
    if (!mOccludedEffect)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
        return;
    const ModelSceneContext::View& view = context.mViews[context.mCurrentView];
    mOccludedEffect->calcView(context._8, view.mView, view.mProjection, view._140, view._144,
                              view._148, view._14c, view._15c);
}

// 0x7100c2f40c: draws the occluded effects into the render buffer's depth target.
void ModelSceneFx::drawOccludedEffect(agl::DrawContext* context,
                                      const ModelSceneContext& scene_context) const {
    if (!mOccludedEffect)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
        return;
    mOccludedEffect->draw(context, scene_context._8, *scene_context.mRenderBuffer,
                          *scene_context.mViewport,
                          *scene_context.mRenderBuffer->getRenderTargetDepth());
}

// 0x7100c300d0
void ModelSceneFx::drawDebug(agl::DrawContext* context,
                             const ModelSceneContext& scene_context) const {
    if (mOccludedEffect) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
            mOccludedEffect->drawDebug(context, scene_context._8);
    }
    if (mDecalAoMgr) {
        if (_8->useDecalAo()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
                mDecalAoMgr->drawDebug(context, scene_context._8);
        }
    }
    if (mVolumeMask) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::VolumeMask)) {
            if (mVolumeMask->_4e0)
                mVolumeMask->drawDebug(context, scene_context._8, 0,
                                       scene_context.mViews[0].mView);
        }
    }
}

}  // namespace gsys
