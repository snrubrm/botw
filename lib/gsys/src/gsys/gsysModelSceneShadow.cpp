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

// 0x7100c3adf0
void ModelSceneShadow::attachHostIO(sead::hostio::Node*) {}

}
