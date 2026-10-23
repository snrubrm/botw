#include "gsys/gsysMaskedLight.h"
#include "gsys/gsysModelSceneShadow.h"
#include "gsys/gsysMaskedSpotLight.h"
#include "gsys/gsysMaskedProjLight.h"

namespace gsys {

// 0x7100c7c460
s32 MaskedSpotLightRig::getTypeID() const {
    return sTypeInfo->id;
}


MaskedLight::MaskedLight()
    : mIsEnableShadow(true, "IsEnableShadow", "影", this),
      mIsEnablePCF(false, "IsEnablePCF", "ソフトシャドウ", this),
      mIsEnableShadowDepthClamp(false, "IsEnableShadowDepthClamp", "シャドウのデプスクランプ有効",
                                this),
      mEnableShadowCtx(0xff, "EnableShadowCtx", "視点毎の影", this),
      mIsLightViewOverride(false, "IsLightViewOverride", "ライトビューオフセット", this),
      mLightViewTrans({0.0f, 0.0f, 0.0f}, "LightViewTrans", "Trans", this),
      mLightViewRotate({0.0f, 0.0f, 0.0f}, "LightViewRotate", "Rotate", this),
      mIsLightProjOverride(false, "IsLightProjOverride", "ライトプロジェクション上書き", this),
      mLightProjNear(0.1f, "LightProjNear", "Near", this),
      mLightProjFar(10.0f, "LightProjFar", "Far", this),
      mLightProjAspect(1.0f, "LightProjAspect", "Aspect", this),
      mLightProjFovy(0.6f, "LightProjFovy", "Fovy", this) {}

MaskedLight::~MaskedLight() = default;

void MaskedLight::initialize(int count, sead::Heap* heap) {
    mViewNum = count;
    initializeImpl_(count, heap);
}

void MaskedLight::update() {
    if (mLightPrePass)
        updateImpl_();
}

void MaskedLight::updateView(const ViewData& view, int view_index) {
    if (mLightPrePass)
        updateViewImpl_(view.view, view.projection, view_index);
}

void MaskedLight::setToLightPrePass(int index, f32 a, f32 b) {
    if (mLightPrePass && isEnable())
        setToLightPrePassImpl_(mLightPrePass, index, a, b);
}

void MaskedLight::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                            const sead::Matrix44f& projection, int view_index) const {
    drawDebugImpl_(context, view, projection, view_index);
}

s32 MaskedLight::getTypeID() const {
    return sTypeInfo->id;
}

void MaskedLight::setShadowMap(int index, const agl::TextureSampler* sampler,
                               const sead::Matrix44f& matrix) const {
    if (!mLightPrePass)
        return;
    if (*mIsEnableShadow && (*mEnableShadowCtx & 1 << index) > 0)
        setShadowMapImpl_(index, mLightPrePass, sampler, matrix);
    else
        setShadowMapImpl_(index, mLightPrePass, nullptr, matrix);
}

bool MaskedLight::assignModelSceneShadow(bool enable) const {
    if (!mModelSceneShadow)
        return false;
    const bool enabled = mModelSceneShadow->isEnableMaskedLightShadow(this);
    if (enable && *mIsEnableShadow && isEnable()) {
        if (!enabled)
            return mModelSceneShadow->enableMaskedLightShadow(this);
    } else if (enabled) {
        return mModelSceneShadow->disableMaskedLightShadow(this);
    }
    return true;
}

// 0x7100c7b39c
s32 MaskedSpotLight::getTypeID() const {
    return sTypeInfo->id;
}

// 0x7100c79d7c
void MaskedSpotLight::drawDebugImpl_(agl::DrawContext*, const sead::Matrix34f&,
                                     const sead::Matrix44f&, int) const {}

// 0x7100c7b52c
s32 MaskedProjLight::getTypeID() const {
    return sTypeInfo->id;
}

// 0x7100c7ac30
void MaskedProjLight::drawDebugImpl_(agl::DrawContext*, const sead::Matrix34f&,
                                     const sead::Matrix44f&, int) const {}

void MaskedLight::initializeImpl_(int, sead::Heap*) {}

void MaskedLight::setToLightPrePassImpl_(agl::lght::LightPrePass*, int, f32, f32) {}

void MaskedLight::updateImpl_() {}

void MaskedLight::updateViewImpl_(const sead::Matrix34f&, const sead::Matrix44f&, int) {}

void MaskedLight::getLightInfo_(agl::lght::LightPrePass*,
                                agl::lght::LightPrePass::LightInfo*) const {}

void MaskedLight::setShadowMapImpl_(int, agl::lght::LightPrePass*, const agl::TextureSampler*,
                                    const sead::Matrix44f&) const {}

void MaskedLight::drawDebugImpl_(agl::DrawContext*, const sead::Matrix34f&,
                                 const sead::Matrix44f&, int) const {}

// 0x7100c79d54
void MaskedSpotLight::getLightInfo_(agl::lght::LightPrePass* light_pre_pass,
                                    agl::lght::LightPrePass::LightInfo* info) const {
    light_pre_pass->getSpotLightInfo(mIndex, info);
}

// 0x7100c7ac08
void MaskedProjLight::getLightInfo_(agl::lght::LightPrePass* light_pre_pass,
                                    agl::lght::LightPrePass::LightInfo* info) const {
    light_pre_pass->getProjLightInfo(mIndex, info);
}

void MaskedLight::genMessageMaskedLight(sead::hostio::Context*) {}

void MaskedLight::listenPropertyEventMaskedLight(const sead::hostio::PropertyEvent*) {}

}  // namespace gsys
