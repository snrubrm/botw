#include "gsys/gsysModelScenePfx.h"

#include <postfx/aglAutoExposure.h>
#include <postfx/aglBloom.h>
#include <postfx/aglColorCorrection.h>
#include <postfx/aglFlareFilter.h>
#include <postfx/aglGlareFilter.h>
#include <postfx/aglHDRCompose.h>

#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelSceneContext.h"

namespace gsys {

// 0x7100c35494
ModelScenePfx::CreateArg::CreateArg() = default;

// 0x7100c36538
void ModelScenePfx::attachHostIO(sead::hostio::Node*) {}

// 0x7100c35a98
bool ModelScenePfx::isHDRComposeEnabled() const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::HDR))
        return false;
    return mHDRCompose != nullptr;
}

// 0x7100c35abc
bool ModelScenePfx::isColorCorrectionEnabled() const {
    if (!mColorCorrection)
        return false;
    return _8->isFeatureEnabled(ModelSceneConfig::Feature::ColorCorrection);
}

// 0x7100c35ae0
bool ModelScenePfx::isBloomEnabled(int view) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Bloom))
        return false;
    if (!mBloom)
        return false;
    return mBloom->isViewEnabled(view);
}

// 0x7100c362e0
void ModelScenePfx::drawAutoExposure(agl::DrawContext* draw_context,
                                     ModelSceneContext* context) const {
    if (!mAutoExposure)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::AutoExposure))
        return;
    mAutoExposure->draw(draw_context, context->getViewIndex(), *context->getRenderBuffer(), nullptr);
}

// 0x7100c3627c
void ModelScenePfx::release(int view) const {
    if (mBloom)
        mBloom->releaseBloomBuffer(view);
    if (mGlareFilter)
        mGlareFilter->releaseGlareBuffer(view);
    if (mFlareFilter && _8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        mFlareFilter->releaseFlareBuffer(view);
}

// 0x7100c35f1c
void ModelScenePfx::drawGlareFilter(agl::DrawContext* draw_context,
                                   const ModelSceneContext& context) const {
    if (!mGlareFilter)
        return;
    const int view = context.getViewIndex();
    if (isBloomEnabled(view))
        mGlareFilter->drawToGlareBuffer(draw_context, view, *context.getRenderBuffer(),
                                        *context.getViewport(), nullptr);
    else
        mGlareFilter->draw(draw_context, view, *context.getRenderBuffer(), *context.getViewport(),
                           nullptr);
}

// 0x7100c35f8c
void ModelScenePfx::drawFlareFilter(agl::DrawContext* draw_context, const ModelSceneContext& context,
                                   const agl::TextureData& texture) const {
    if (!mFlareFilter)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        return;
    const int view = context.getViewIndex();
    if (isBloomEnabled(view))
        mFlareFilter->drawToFlareBuffer(draw_context, view, texture, 2, 2);
    else
        mFlareFilter->draw(draw_context, view, *context.getRenderBuffer(), *context.getViewport(),
                           texture, 2, 2);
}

// 0x7100c36310
void ModelScenePfx::drawDebug(agl::DrawContext* draw_context,
                              const ModelSceneContext& context) const {
    if (mGlareFilter)
        mGlareFilter->drawDebug(draw_context, context.getViewIndex());
    if (mFlareFilter && _8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        mFlareFilter->drawDebug(draw_context, context.getViewIndex());
    if (mAutoExposure && _8->isFeatureEnabled(ModelSceneConfig::Feature::AutoExposure))
        mAutoExposure->drawDebug(draw_context, context.getViewIndex(), *context.getRenderBuffer(),
                                 nullptr);
}

// 0x7100c363a4
void ModelScenePfx::calcGPU() {
    if (mAutoExposure && _8->isFeatureEnabled(ModelSceneConfig::Feature::AutoExposure))
        mAutoExposure->calcGPU();
    if (mGlareFilter)
        mGlareFilter->calcGPU();
    if (mFlareFilter && _8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        mFlareFilter->calcGPU();
}

// 0x7100c36404
void ModelScenePfx::calcViewGPU(const ModelSceneContext& context) {
    if (mGlareFilter)
        mGlareFilter->calcViewGPU(context.getViewIndex());
    if (mFlareFilter && _8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        mFlareFilter->calcViewGPU(context.getViewIndex());
}

// 0x7100c36458
void ModelScenePfx::calcGPUDrawBackGround() const {
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Bloom) && mBloom && mBloom->_7a0 &&
        mBloom->mViewMask != 0)
        mBloom->calcGPU();
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::HDR) && mHDRCompose)
        mHDRCompose->calcGPU();
}

}  // namespace gsys
