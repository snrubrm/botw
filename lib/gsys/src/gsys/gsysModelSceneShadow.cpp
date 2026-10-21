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

}
