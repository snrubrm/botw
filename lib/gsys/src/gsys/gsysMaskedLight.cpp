#include "gsys/gsysMaskedLight.h"

namespace gsys {

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

void MaskedLight::genMessageMaskedLight(sead::hostio::Context*) {}

void MaskedLight::listenPropertyEventMaskedLight(const sead::hostio::PropertyEvent*) {}

}  // namespace gsys
