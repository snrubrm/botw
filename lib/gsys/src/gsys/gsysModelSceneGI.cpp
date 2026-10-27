#include "gsys/gsysModelSceneGI.h"
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysShaderContext.h"

namespace gsys {

// 0x7100c309f0
bool ModelSceneGI::isEnvCubeMapEnabled() const {
    return mEnvCubeMap && _8->isFeatureEnabled(ModelSceneConfig::Feature::EnvCubeMap);
}

// 0x7100c32bf8
bool ModelSceneGI::isLightPrePassEnabled() const {
    return mLightPrePass && _8->isFeatureEnabled(ModelSceneConfig::Feature::LightPrePass);
}

// 0x7100c33f3c
bool ModelSceneGI::isPlanarReflectionEnabled() const {
    return mPlanarReflection && _8->isFeatureEnabled(ModelSceneConfig::Feature::Reflection);
}

// 0x7100c33f90
bool ModelSceneGI::isSSIIEnabled() const {
    return mSSII && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSII);
}

// 0x7100c348c8
agl::env::CubeMapMgr* ModelSceneGI::getCubeMapMgr() {
    return mEnvCubeMap ? &mEnvCubeMap->mCubeMapMgr : nullptr;
}

// 0x7100c348dc
bool ModelSceneGI::isCubeMapReady() const {
    return mEnvCubeMap && mEnvCubeMap->mCubeMap != nullptr;
}

// 0x7100c324e8
void ModelSceneGI::pushBack(const sead::Vector3f&, agl::lght::LocalLightMapObj* obj) {
    const s32 index = mCount++;
    mObjects[index] = obj;
}

// 0x7100c309d0
void ModelSceneGI::setSceneMaterial(ModelNW* model) {
    if (!mEnvCubeMap)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::EnvCubeMap))
        return;
    mEnvCubeMap->mShaderContext->setSceneMaterial(model);
}

}  // namespace gsys
