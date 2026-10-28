#include <gsys/gsysModelSceneFx.h>

#include <environment/aglEnvObjMgr.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelRig.h>
#include <gsys/gsysModelSceneConfig.h>
#include <gsys/gsysModelSceneContext.h>
#include <gsys/gsysEffectRadialBlurMgr.h>
#include <gsys/gsysOfxLensFlareRig.h>
#include <gsys/gsysParticleScene.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <common/aglDrawContext.h>
#include <effect/aglFxOfxBase.h>
#include <common/aglRenderBuffer.h>
#include <effect/aglFxCloud.h>
#include <effect/aglFxDecalAoMgr.h>
#include <effect/aglFxDecalDrawer.h>
#include <effect/aglFxDecalSimple.h>
#include <effect/aglFxDecalTrailMgr.h>
#include <effect/aglFxNormalDrawer.h>
#include <effect/aglFxOfxBase.h>
#include <effect/aglFxRadialBlur.h>
#include <effect/aglFxVolumeMask.h>

namespace gsys {

// 0x7100c304a4 / 0x7100c30780: the two rig managers only own the four pointer arrays and
// the two object buffers; the original frees the object group before the hook group.
template <>
ModelSceneFx::OfxResMgr<OfxLensFlareRig, OfxLensFlareImpl>::~OfxResMgr() {
    mFreeObjs.freeBuffer();
    mActiveObjs.freeBuffer();
    mObjBuffer.freeBuffer();
    mFreeHooks.freeBuffer();
    mActiveHooks.freeBuffer();
    mHookBuffer.freeBuffer();
}

template <>
ModelSceneFx::OfxResMgr<OfxLargeLensFlareRig, OfxLargeLensFlareImpl>::~OfxResMgr() {
    mFreeObjs.freeBuffer();
    mActiveObjs.freeBuffer();
    mObjBuffer.freeBuffer();
    mFreeHooks.freeBuffer();
    mActiveHooks.freeBuffer();
    mHookBuffer.freeBuffer();
}

// 0x7100c301cc (Large) / 0x7100c30338 (Lens): unbinds every hook of `rig` from `model`
// and returns it to the free list.
// NON_MATCHING: the original's scan loops keep pointer-end iteration; clang 4 turns these
// indexed loops into a countdown and the function is 0x24 bytes shorter.
template <typename Rig, typename Impl>
void ModelSceneFx::OfxResMgr<Rig, Impl>::release(Rig* rig, Model* model, int unit_index) {
    OfxHook** const data = mActiveHooks.data();
    for (s32 i = 0; i != mActiveHooks.size(); ++i) {
        OfxHook* hook = data[i];
        if (hook->mRig != rig || hook->mModel != model || hook->mUnitIndex != unit_index)
            continue;

        hook->mModel = nullptr;
        hook->mPreviousUnitIndex = -1;
        hook->mUnitIndex = -1;
        model->erase(unit_index, hook);

        for (s32 j = 0; j != mActiveHooks.size(); ++j) {
            if (data[j] != hook)
                continue;
            mActiveHooks.erase(j);
            mFreeHooks.pushBack(hook);

            if (hook->mObj)
                hook->mObj->mHook = nullptr;
            if (hook->mRig)
                hook->mRig->mHooks.erase(hook);
            hook->mRig = nullptr;
            hook->mObj = nullptr;
            hook->mModel = nullptr;
            hook->mVisible = 0xffff;
            hook->mPreviousVisible = 0xffff;
            break;
        }

        // The hook list shrank; restart the scan from the first entry.
        i = -1;
    }
}

template void ModelSceneFx::OfxResMgr<OfxLensFlareRig, OfxLensFlareImpl>::release(
    OfxLensFlareRig*, Model*, int);
template void ModelSceneFx::OfxResMgr<OfxLargeLensFlareRig, OfxLargeLensFlareImpl>::release(
    OfxLargeLensFlareRig*, Model*, int);

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

// 0x7100c2edf4: the radial blur and the cloud run their CPU-side calculation.
void ModelSceneFx::calc(ParticleScene* scene) {
    if (mRadialBlur) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::RadialBlur)) {
            scene->mEffectRadialBlurMgr->setRadialBlur(scene, *mRadialBlur);
            mRadialBlur->calc();
        }
    }
    if (mCloud) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Cloud)) {
            if (mCloud->_460) {
                mCloud->_7724 = _2d8;
                mCloud->calc();
            }
        }
    }
}

// 0x7100c2f2b4: each decal pass runs when its feature and its own parameter are enabled.
void ModelSceneFx::calcDecal() {
    if (mDecalDrawer) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal)) {
            if (mDecalDrawer->_478)
                mDecalSimple->updateGPU();
        }
    }
    if (mDecalAoMgr) {
        if (_8->useDecalAo()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
                mDecalAoMgr->calc();
        }
    }
    if (mDecalTrailMgr) {
        if (_8->useDecalTrail()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
                mDecalTrailMgr->calc();
        }
    }
    if (mNormalDrawer) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::NormalDrawer))
            mNormalDrawer->calc();
    }
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

// 0x7100c2ff0c: per-view GPU setup for every effect manager.
// NON_MATCHING: same instructions and size, but the cloud block's tail is scheduled differently
// (the original emits mov w5 / ldp / madd / the two scalar loads / ldrb w1 / cset / add; ours
// issues ldrb w1 and mov w5 before the cset).
void ModelSceneFx::calcViewGPU(const ModelSceneContext& context) {
    if (mOccludedEffect) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
            mOccludedEffect->updateViewGPU(context.getViewIndex(), *context.getRenderBuffer());
    }
    if (mRadialBlur) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::RadialBlur))
            mRadialBlur->updateViewGPU(context.getViewIndex());
    }
    if (mDecalDrawer) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal)) {
            if (mDecalDrawer->_478) {
                mDecalDrawer->calcGPU(context.getViewIndex());
                const ModelRenderContext::ViewData& view = context.getViewData()[0];
                mDecalSimple->calcGPU(context.getViewIndex(), view.frustum.getViewMatrix(), view.frustum.getProjectionMatrix(), view.frustum.getNear(), view.frustum.getFar(),
                                      view.frustum.get_f4(), view.frustum.getAspect());
            }
        }
    }
    if (mDecalAoMgr) {
        if (_8->useDecalAo()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal)) {
                const ModelRenderContext::ViewData& view = context.getViewData()[0];
                mDecalAoMgr->calcGPU(context.getViewIndex(), view.frustum.getViewMatrix(), view.frustum.getProjectionMatrix(), view.frustum.getNear(), view.frustum.getFar(),
                                     view.frustum.get_f4(), view.frustum.getAspect());
            }
        }
    }
    if (mDecalTrailMgr) {
        if (_8->useDecalTrail()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal)) {
                const ModelRenderContext::ViewData& view = context.getViewData()[0];
                mDecalTrailMgr->calcGPU(context.getViewIndex(), view.frustum.getViewMatrix(), view.frustum.getProjectionMatrix(), view.frustum.getNear(),
                                        view.frustum.getFar(), view.frustum.get_f4(), view.frustum.getAspect());
            }
        }
    }
    if (mNormalDrawer) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::NormalDrawer)) {
            const ModelRenderContext::ViewData& view = context.getViewData()[0];
            mNormalDrawer->calcGPU(context.getViewIndex(), view.frustum.getViewMatrix(), view.frustum.getNear(), view.frustum.getFar(), 1280.0f, 720.0f);
        }
    }
    if (mCloud) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Cloud)) {
            if (mCloud->_460) {
                const bool alloc_buffer = mCloud->_618 == 0;
                const ModelRenderContext::ViewData& view = context.getViewData()[context.mCurrentView];
                mCloud->updateViewGPU(context.getViewIndex(), view.view, view.frustum.getProjectionMatrix(), view.frustum.getNear(),
                                      view.frustum.getFar(), alloc_buffer, 0);
            }
        }
    }
}

// 0x7100c2f390: the scene's radial blur follows the first view's matrices.
void ModelSceneFx::calcView(const ModelSceneContext& context) {
    if (!mRadialBlur)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::RadialBlur))
        return;
    mRadialBlur->calcView(context.getViewIndex(), context.getViewData()[0].view, context.getViewData()[0].frustum.getProjectionMatrix());
}

// 0x7100c2f3c0: the occluded effects follow the current view's matrices and factors.
void ModelSceneFx::calcViewOccludedEffect(const ModelSceneContext& context) {
    if (!mOccludedEffect)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
        return;
    const ModelRenderContext::ViewData& view = context.getViewData()[context.mCurrentView];
    mOccludedEffect->calcView(context.getViewIndex(), view.view, view.frustum.getProjectionMatrix(), view.frustum.getNear(), view.frustum.getFar(),
                              view.frustum.getFovy(), view.frustum.getAspect(), view.frustum.getOffset());
}

// 0x7100c2f40c: draws the occluded effects into the render buffer's depth target.
void ModelSceneFx::drawOccludedEffect(agl::DrawContext* context,
                                      const ModelSceneContext& scene_context) const {
    if (!mOccludedEffect)
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
        return;
    mOccludedEffect->draw(context, scene_context.getViewIndex(), *scene_context.getRenderBuffer(),
                          *scene_context.getViewport(),
                          *scene_context.getRenderBuffer()->getRenderTargetDepth());
}

// 0x7100c300d0
void ModelSceneFx::drawDebug(agl::DrawContext* context,
                             const ModelSceneContext& scene_context) const {
    if (mOccludedEffect) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::OccludedEffect))
            mOccludedEffect->drawDebug(context, scene_context.getViewIndex());
    }
    if (mDecalAoMgr) {
        if (_8->useDecalAo()) {
            if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Decal))
                mDecalAoMgr->drawDebug(context, scene_context.getViewIndex());
        }
    }
    if (mVolumeMask) {
        if (_8->isFeatureEnabled(ModelSceneConfig::Feature::VolumeMask)) {
            if (mVolumeMask->_4e0)
                mVolumeMask->drawDebug(context, scene_context.getViewIndex(), 0,
                                       scene_context.getViewData()[0].view);
        }
    }
}

// 0x7100c2e904: drops the old rigs, then forwards the model to the ModelRig object of every
// lens-flare rig of both types. The dynamic cast is trusted (the original dereferences its
// result without a null test).
// NON_MATCHING: same size and instruction set, but the loop preheader is scheduled differently
// (the original delays the count-1 subtraction until after the typeinfo guard setup and keeps
// the sign-extended type id in w11).
void ModelSceneFx::bind(Model* model) {
    unbind(model);
    if (!mOccludedEffect)
        return;
    const s32 num_large = mEnvObjMgr->getObjectNum(OfxLargeLensFlareRig::sTypeInfo->id);
    for (s32 i = 0; i <= num_large - 1; ++i) {
        OfxLargeLensFlareRig* rig = sead::DynamicCast<OfxLargeLensFlareRig>(
            mEnvObjMgr->getObject(OfxLargeLensFlareRig::sTypeInfo->id, i));
        rig->m23(model);
    }
    const s32 num_lens = mEnvObjMgr->getObjectNum(OfxLensFlareRig::sTypeInfo->id);
    for (s32 i = 0; i <= num_lens - 1; ++i) {
        OfxLensFlareRig* rig = sead::DynamicCast<OfxLensFlareRig>(
            mEnvObjMgr->getObject(OfxLensFlareRig::sTypeInfo->id, i));
        rig->m23(model);
    }
}

// 0x7100c2eb6c: releases the Lens and Large rigs of every model unit from the two managers.
void ModelSceneFx::unbind(Model* model) {
    if (!mOccludedEffect)
        return;

    const s32 num_large = mEnvObjMgr->getObjectNum(OfxLargeLensFlareRig::sTypeInfo->id);
    for (s32 i = 0; i < num_large; ++i) {
        for (s32 j = 0; j < model->getUnits().size(); ++j) {
            OfxLargeLensFlareRig* rig = sead::DynamicCast<OfxLargeLensFlareRig>(
                mEnvObjMgr->getObject(OfxLargeLensFlareRig::sTypeInfo->id, i));
            mOfxLargeLensFlare->release(rig, model, j);
        }
    }

    const s32 num_lens = mEnvObjMgr->getObjectNum(OfxLensFlareRig::sTypeInfo->id);
    for (s32 i = 0; i < num_lens; ++i) {
        for (s32 j = 0; j < model->getUnits().size(); ++j) {
            OfxLensFlareRig* rig = sead::DynamicCast<OfxLensFlareRig>(
                mEnvObjMgr->getObject(OfxLensFlareRig::sTypeInfo->id, i));
            mOfxLensFlare->release(rig, model, j);
        }
    }
}

// 0x7100c2fb7c: draws the cloud, then finishes its render texture and rebinds this context.
void ModelSceneFx::drawCloud(agl::DrawContext* context,
                             const ModelSceneContext* scene_context) const {
    agl::fx::Cloud* cloud = mCloud;
    if (_8->isFeatureEnabled(ModelSceneConfig::Feature::Cloud) && cloud->_460) {
        cloud->draw(context, scene_context->getViewIndex(), *scene_context->getRenderBuffer(), 0);
    }
    if (mCloud->_618) {
        mCloud->finishRenderTexture(context, scene_context->getViewIndex());
        scene_context->bind(context);
    }
}

// 0x7100c30184
void ModelSceneFx::attachHostIO(sead::hostio::Node*) {}

}  // namespace gsys

namespace gsys {

template <typename Impl>
OfxRig<Impl>::OfxObj::~OfxObj() {}

template <typename Impl>
OfxRig<Impl>::OfxHook::~OfxHook() {}

// NON_MATCHING: our clang folds the 16-bit test into the AND (one instruction less).
template <typename Impl>
void OfxRig<Impl>::OfxHook::updateFromModel(ModelUnit* unit, u32 visibility_mask, f32) {
    const u16 visible = unit->getVisibilityMask() & visibility_mask;
    mVisible = visible != 0;
}

template <typename Impl>
void OfxRig<Impl>::bindBone_(Model*, const BoneAccessKey&, const sead::SafeString&) {}

template <typename Impl>
void OfxRig<Impl>::bindMaterial_(Model*, const MaterialAccessKey&, const sead::SafeString&) {}

template <typename Impl>
void OfxRig<Impl>::release_(Model*, int) {}

template OfxRig<OfxLensFlareImpl>::OfxObj::~OfxObj();
template OfxRig<OfxLensFlareImpl>::OfxHook::~OfxHook();
template OfxRig<OfxLargeLensFlareImpl>::OfxObj::~OfxObj();
template OfxRig<OfxLargeLensFlareImpl>::OfxHook::~OfxHook();
template void OfxRig<OfxLensFlareImpl>::bindBone_(Model*, const BoneAccessKey&,
                                                  const sead::SafeString&);
template void OfxRig<OfxLensFlareImpl>::bindMaterial_(Model*, const MaterialAccessKey&,
                                                      const sead::SafeString&);
template void OfxRig<OfxLensFlareImpl>::release_(Model*, int);
template void OfxRig<OfxLensFlareImpl>::OfxHook::updateFromModel(ModelUnit*, u32, f32);
template void OfxRig<OfxLargeLensFlareImpl>::bindBone_(Model*, const BoneAccessKey&,
                                                       const sead::SafeString&);
template void OfxRig<OfxLargeLensFlareImpl>::bindMaterial_(Model*, const MaterialAccessKey&,
                                                           const sead::SafeString&);
template void OfxRig<OfxLargeLensFlareImpl>::release_(Model*, int);
template void OfxRig<OfxLargeLensFlareImpl>::OfxHook::updateFromModel(ModelUnit*, u32, f32);

}  // namespace gsys

namespace agl::fx {

// 0x7100c2e900
OccludedEffectMgr::CreateArg::~CreateArg() {}

}  // namespace agl::fx
