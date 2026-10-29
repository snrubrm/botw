#include <gsys/gsysModelSceneShadow.h>
#include <gsys/gsysModelSceneConfig.h>
#include <gsys/gsysModelSceneContext.h>
#include <shadow/aglSSAO.h>
#include <shadow/aglShadowPrePass.h>

namespace gsys {

// 0x7100c38558
bool ModelSceneShadow::isShadowPrePassEnabled() const {
    if (!mShadowPrePass)
        return false;
    if (!mConfig->isFeatureEnabled(ModelSceneConfig::Feature::ShadowPrePass))
        return false;
    return mShadowPrePass->_478;
}

// 0x7100c3a898
bool ModelSceneShadow::isSSAOEnabled() const {
    if (!mSSAO)
        return false;
    return mConfig->isFeatureEnabled(ModelSceneConfig::Feature::SSAO);
}

// 0x7100c3acf4
bool ModelSceneShadow::isDepthShadowEnabled() const {
    if (!mConfig->shouldCreateFeature(ModelSceneConfig::Feature::DepthShadow))
        return false;
    return mConfig->isFeatureEnabled(ModelSceneConfig::Feature::DepthShadow);
}

// 0x7100c3ad18
bool ModelSceneShadow::enableMaskedLightShadow(const MaskedLight* light) {
    MaskedLightShadow* slot = mMaskedLightShadows;
    for (int i = mMaskedLightShadowNum; i != 0; ++slot, --i) {
        if (!slot->mLight) {
            slot->mLight = light;
            return true;
        }
    }
    return false;
}

// 0x7100c3ad58
bool ModelSceneShadow::disableMaskedLightShadow(const MaskedLight* light) {
    MaskedLightShadow* slot = mMaskedLightShadows;
    for (int i = mMaskedLightShadowNum; i != 0; ++slot, --i) {
        if (slot->mLight == light) {
            slot->mLight = nullptr;
            return true;
        }
    }
    return false;
}

// 0x7100c3ad9c
bool ModelSceneShadow::isEnableMaskedLightShadow(const MaskedLight* light) const {
    if (!mConfig->isFeatureEnabled(ModelSceneConfig::Feature::MaskedLight))
        return false;
    const MaskedLightShadow* slot = mMaskedLightShadows;
    for (int i = mMaskedLightShadowNum; i != 0; ++slot, --i) {
        if (slot->mLight == light)
            return true;
    }
    return false;
}

// 0x7100c3ab50
void ModelSceneShadow::releaseSSAO(ModelSceneContext* context) const {
    if (!mSSAO)
        return;
    if (!mConfig->isFeatureEnabled(ModelSceneConfig::Feature::SSAO))
        return;
    mSSAO->release(context->getViewIndex());
}

// 0x7100c3a8bc
void ModelSceneShadow::releaseShadowPrePass(ModelSceneContext* context) const {
    if (!mShadowPrePass || !mConfig->isFeatureEnabled(ModelSceneConfig::Feature::ShadowPrePass))
        return;
    if (!mShadowPrePass->_478)
        return;
    mShadowPrePass->release(context->getViewIndex());
    context->popPassTexture(ModelRenderContext::PassTextureType(4));
}

// 0x7100c3ab74
void ModelSceneShadow::drawDebug(agl::DrawContext* draw_context,
                                 const ModelSceneContext& context) const {
    if ((_444 & 1) == 0)
        return;
    if (!mConfig->isFeatureEnabled(ModelSceneConfig::Feature::StaticDepthShadow))
        return;
    const ModelRenderContext::ViewData& view = context.getViewData()[0];
    mStaticDepthShadow.drawDebug(draw_context, view.view,
                                 view.frustum.getProjectionMatrix());
}

// 0x7100c3adf0
void ModelSceneShadow::attachHostIO(sead::hostio::Node*) {}

namespace {

// inline-only in the original; name is a guess.
f32 clamp01(f32 value) {
    f32 result = 0.0f;
    if (!(value < 0.0f)) {
        result = value;
        if (value > 1.0f)
            result = 1.0f;
    }
    return result;
}

}  // namespace

// 0x7100c3a06c
f32 ModelSceneShadow::ProjectionShadowInfo::getDensity(int view) const {
    const ViewInfo& info = (view == 1 && _5b0) ? mViewInfo1 : mViewInfo0;
    const f32 density = clamp01(info.mDensity);
    const f32 scale = (view == 1) ? _638 : _634;
    return density * clamp01(scale);
}

}
