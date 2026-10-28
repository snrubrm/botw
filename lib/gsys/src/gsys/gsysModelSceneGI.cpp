#include "gsys/gsysModelSceneGI.h"
#include "gsys/gsysLayer3D.h"
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysShaderContext.h"
#include "gsys/gsysModelSceneContext.h"
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <lighting/aglLightMapMgr.h>
#include <lighting/aglLightPrePass.h>
#include <lighting/aglPlanarReflection.h>
#include <lighting/aglLocalReflection.h>
#include <lighting/aglSSII.h>
#include <lighting/aglSSSSS.h>
#include <mc/seadCoreInfo.h>
#include "gsys/gsysLightProbeMgr.h"
#include "gsys/gsysLayer3D.h"

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
    mObjects.pushBack(obj);
}

// 0x7100c3250c
void ModelSceneGI::calcWorld() {
    for (auto& obj : mObjects)
        mFrameObjects.pushBack(&obj);
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::LightProbe) && mLightProbeMgr &&
        mLightProbeMgr->isEnabled())
        mLightProbeMgr->calc();
    if (mEnvCubeMap && _8->isFeatureEnabled(ModelSceneConfig::Feature::EnvCubeMap))
        mEnvCubeMap->update();
}

// 0x7100c347d0
void ModelSceneGI::calcGPU() {
    if (mSSSSS && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSSSS))
        mSSSSS->calcGPU();
    if (mSSII && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSII))
        mSSII->calcGPU();
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::LightProbe) && mLightProbeMgr &&
        mLightProbeMgr->isEnabled())
        mLightProbeMgr->calcGPU();
}

// 0x7100c32ccc
void ModelSceneGI::calcGPUDrawBackGround() const {
    if (mLightMapMgr && _8->isFeatureEnabled(ModelSceneConfig::Feature::LightMap))
        mLightMapMgr->updateGPU();
    if (mLightPrePass && _8->isFeatureEnabled(ModelSceneConfig::Feature::LightPrePass))
        mLightPrePass->updateGPU();
}

// 0x7100c32c1c
void ModelSceneGI::calcViewLightPrePass(const ModelSceneContext& context) {
    if (!mLightPrePass || !_8->isFeatureEnabled(ModelSceneConfig::Feature::LightPrePass))
        return;
    const s32 view_index = context.getViewIndex();
    const ModelRenderContext::ViewData* view = context.getViewData();
    mLightPrePass->calcContext(view_index, view->view,
                               view->frustum.getProjectionMatrix(), view->frustum.getNear(),
                               view->frustum.getFar(), view->frustum.getFovy(),
                               view->frustum.getAspect(), view->frustum.getOffset());
}

// 0x7100c32c60
void ModelSceneGI::calcView(const ModelSceneContext& context) {
    if (((context.mFlags >> 2) & 1) && mLightMapMgr &&
        _8->isFeatureEnabled(ModelSceneConfig::Feature::LightMap))
        mLightMapMgr->update();
    if (mSSSSS && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSSSS))
        mSSSSS->calcView(context.getViewIndex(), context.getViewData()->frustum);
}

// 0x7100c32288
void ModelSceneGI::sssssCallback(const agl::lght::SSSSS::CallbackArg& arg) const {
    const s32 core = int(sead::CoreInfo::getCurrentCoreId());
    mContexts[core]->drawQueue(arg.mDrawContext, "Model(SSSSS)", ModelSceneContext::QueueType(0),
                               sead::BitFlag32(0x80), 0, ModelEnum::ShaderAssignType::_6,
                               ModelSceneContext::ViewProjType(0), 0, 0xffff);
}

// 0x7100c33fb4
void ModelSceneGI::calcViewLightProbe(const ModelSceneContext& context) {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::LightProbe) || !mLightProbeMgr ||
        !mLightProbeMgr->isEnabled())
        return;
    const sead::Matrix44f projection =
        context._398->getRenderProjection()->getProjectionMatrix();
    const sead::Matrix34f view = context._398->sub_7100B60CE0()->getMatrix();
    mLightProbeMgr->calcView(context.getViewIndex(), projection, view);
}

// 0x7100c33f60
void ModelSceneGI::calcViewSSII(const ModelSceneContext& context) {
    if (!mSSII || !_8->isFeatureEnabled(ModelSceneConfig::Feature::SSII))
        return;
    mSSII->calcView(context.getViewIndex(), context.getViewData()->frustum);
}

// 0x7100c34844
void ModelSceneGI::calcViewGPU(const ModelSceneContext& context) {
    if (mSSSSS && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSSSS))
        mSSSSS->calcViewGPU(context.getViewIndex());
    if (mSSII && _8->isFeatureEnabled(ModelSceneConfig::Feature::SSII))
        mSSII->calcViewGPU(context.getViewIndex());
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::LightProbe) && mLightProbeMgr &&
        mLightProbeMgr->isEnabled())
        mLightProbeMgr->calcGPU(context.getViewIndex());
}

// 0x7100c33274
void ModelSceneGI::releaseLightPrePass(const ModelSceneContext& context) const {
    if (!mLightPrePass || !_8->isFeatureEnabled(ModelSceneConfig::Feature::LightPrePass))
        return;
    mLightPrePass->release(context.getViewIndex());
}

// 0x7100c3423c
void ModelSceneGI::releasePlanarReflection(const ModelSceneContext& context) const {
    if (!mPlanarReflection || !_8->isFeatureEnabled(ModelSceneConfig::Feature::Reflection))
        return;
    mPlanarReflection->release(context.getViewIndex());
}

// 0x7100c340b8
bool ModelSceneGI::isLocalReflectionEnabled() const {
    return mLocalReflection && _8->isFeatureEnabled(ModelSceneConfig::Feature::LocalReflection) &&
           mLocalReflection->mEnabled != 0;
}

// 0x7100c347a4
void ModelSceneGI::releaseLocalReflection(const ModelSceneContext& context) const {
    if (!mLocalReflection || !_8->isFeatureEnabled(ModelSceneConfig::Feature::LocalReflection))
        return;
    if (!mLocalReflection->mEnabled)
        return;
    mLocalReflection->releaseReflectionBuffer(context.getViewIndex());
}

// 0x7100c33344
void ModelSceneGI::releaseSSSSS(const ModelSceneContext& context) const {
    if (!mSSSSS || !_8->isFeatureEnabled(ModelSceneConfig::Feature::SSSSS))
        return;
    if ((context._3ca & 1) == 0)
        return;
    mSSSSS->release(context.getViewIndex());
}

// 0x7100c309d0
void ModelSceneGI::setSceneMaterial(ModelNW* model) {
    if (!mEnvCubeMap)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::EnvCubeMap))
        return;
    mEnvCubeMap->mShaderContext->setSceneMaterial(model);
}

// NON_MATCHING: same instructions; clang materialises the first view record's matrix address
// before the projection call where the original keeps the record pointer.
// 0x7100c33e7c
void ModelSceneGI::preCalcView(ModelSceneContext* context) {
    if (!mPlanarReflection || !_8->isFeatureEnabled(ModelSceneConfig::Feature::Reflection))
        return;
    mPlanarReflection->calcView(context->getViewIndex(), *context->_398->sub_7100B60CE0());
    context->calcView(1, mPlanarReflection->getView(context->getViewIndex())._510,
                      *context->_398->getRenderProjection(),
                      mPlanarReflection->getView(context->getViewIndex())._510);
}

// 0x7100c34040
void ModelSceneGI::calcViewLocalReflection(ModelSceneContext* context) {
    if (!mLocalReflection || !_8->isFeatureEnabled(ModelSceneConfig::Feature::LocalReflection))
        return;
    if (!mLocalReflection->mEnabled)
        return;
    mLocalReflection->calcView(context->getViewIndex(), *context->_398->sub_7100B60CE0(),
                               *context->_398->getRenderProjection());
}

// 0x7100c3246c
void ModelSceneGI::calcFrame(int frame) {
    if (mLightMapMgr && _8->isFeatureEnabled(ModelSceneConfig::Feature::LightMap))
        mLightMapMgr->constructMemory();
    mObjects.clear();
    mFrameObjects.clear();
    if (mEnvCubeMap && _8->isFeatureEnabled(ModelSceneConfig::Feature::EnvCubeMap))
        mEnvCubeMap->calc(frame);
}

// 0x7100c33a70
void ModelSceneGI::free(PointLightRig* rig, Model* model, int index) {
    if (mPointLightResMgr)
        mPointLightResMgr->free(rig, model, index);
}

// 0x7100c33c04
void ModelSceneGI::free(SpotLightRig* rig, Model* model, int index) {
    if (mSpotLightResMgr)
        mSpotLightResMgr->free(rig, model, index);
}

// 0x7100c33d8c
void ModelSceneGI::free(MaskedSpotLightRig* rig, Model* model, int index) {
    if (mMaskedSpotLightResMgr)
        mMaskedSpotLightResMgr->free(rig, model, index);
}

}  // namespace gsys
