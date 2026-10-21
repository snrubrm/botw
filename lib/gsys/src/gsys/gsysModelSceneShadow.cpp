#include <gsys/gsysModelSceneShadow.h>
#include <gsys/gsysModelSceneConfig.h>

namespace gsys {

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

// 0x7100c3adf0
void ModelSceneShadow::attachHostIO(sead::hostio::Node*) {}

}
