#include "gsys/gsysModelScenePfx.h"

#include <postfx/aglAutoExposure.h>
#include <postfx/aglBloom.h>
#include <postfx/aglColorCorrection.h>
#include <postfx/aglDepthOfField.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <postfx/aglFlareFilter.h>
#include <postfx/aglGlareFilter.h>
#include <postfx/aglHDRCompose.h>

#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelSceneGI.h"
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

// NON_MATCHING: same size and instruction set; only the register colour of the view-mask test
// differs.
// 0x7100c35e9c
void ModelScenePfx::drawDOF(agl::DrawContext* draw_context, ModelSceneContext* context,
                            const agl::TextureData* texture) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::DOF))
        return;
    if (!mDepthOfField)
        return;
    if (!mDepthOfField->isEnabled())
        return;
    const int view = context->getViewIndex();
    if (!mDepthOfField->isViewEnabled(view))
        return;
    if (texture)
        mDepthOfField->draw(draw_context, view, *context->getRenderBuffer(), *texture, true,
                            context->getViewData()[0].frustum.getNear(),
                            context->getViewData()[0].frustum.getFar());
    else if (context->getRenderBuffer()->getRenderTargetDepth())
        mDepthOfField->draw(draw_context, view, *context->getRenderBuffer(),
                            context->getViewData()[0].frustum.getNear(),
                            context->getViewData()[0].frustum.getFar());
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

// NON_MATCHING: same body; the bloom-buffer flag's set/reset is a branch where the original
// if-converts it to orr/and/csel.
// 0x7100c35904
void ModelScenePfx::calc(const ModelSceneGI& gi, f32, bool flag) {
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::HDR) && mHDRCompose) {
        const bool color_correction =
            mColorCorrection && _8->isFeatureEnabled(ModelSceneConfig::Feature::ColorCorrection) &&
            mColorCorrection->getEnableMaybe() && mColorCorrection->getFlagsMaybe() != 0;
        const bool bloom = _8->isFeatureEnabled(ModelSceneConfig::Feature::Bloom) && mBloom &&
                           mBloom->_7a0 && mBloom->mViewMask != 0 && mBloom->_438 - 1 <= 1 &&
                           (mFlags & 1) != 0;
        mHDRCompose->mFlags.changeBit(1, color_correction);
        mHDRCompose->mFlags.changeBit(0, bloom);
        if (bloom)
            mHDRCompose->_1c = mBloom->_438 == 2;
        mHDRCompose->mFlags.changeBit(2, flag);
        mHDRCompose->mFlags.resetBit(3);
        mHDRCompose->calc();
    }

    if (mGlareFilter) {
        s32 glare_count = 0;
        gi.setPointLightGlareFilter(glare_count, mGlareFilter);
        mGlareFilter->_3f8 = glare_count;
        mGlareFilter->calc();
    }

    if (mFlareFilter && _8->isFeatureEnabled(ModelSceneConfig::Feature::FlareFilter))
        mFlareFilter->calc();

    if (mAutoExposure && _8->isFeatureEnabled(ModelSceneConfig::Feature::AutoExposure))
        mAutoExposure->calc();
}

// NON_MATCHING: same size and instruction set; the view-mask `and` has its operands swapped.
// 0x7100c364bc
void ModelScenePfx::calcGPUDrawBackGround(ModelSceneContext* context) const {
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Bloom)) {
        if (mBloom && mBloom->isViewEnabled(context->getViewIndex()))
            mBloom->calcGPU(context->getViewIndex());
    }
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::HDR)) {
        if (mHDRCompose)
            mHDRCompose->calcGPU(context->getViewIndex());
    }
}

// NON_MATCHING: same size; the argument's clear stores are grouped differently and the view-mask
// `and` has its operands swapped.
// 0x7100c3600c
void ModelScenePfx::drawBloom(agl::DrawContext* draw_context, ModelSceneContext* context,
                              const agl::TextureData* texture) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Bloom))
        return;
    if (!mBloom)
        return;
    if (!mBloom->isViewEnabled(context->getViewIndex()))
        return;

    agl::pfx::Bloom::DrawArg arg = {};
    arg.mRenderBuffer = context->getRenderBuffer();
    arg.mViewport = context->getViewport();
    arg.mDepthTexture = texture;
    arg._28 = arg.mRenderBuffer->getRenderTargetColor(0);
    arg.mIsColor = texture && !texture->isDepthFormat();

    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::HDR) && (mFlags & 1) != 0)
        mBloom->drawToBloomBuffer(draw_context, context->getViewIndex(), arg);
    else
        mBloom->draw(draw_context, context->getViewIndex(), arg);
}

}  // namespace gsys
