#pragma once

#include <environment/aglEnvObj.h>
#include <lighting/aglLightPrePass.h>
#include <math/seadMatrix.h>

namespace agl {
class TextureSampler;
}

namespace sead::hostio {
class Context;
class PropertyEvent;
}  // namespace sead::hostio

namespace gsys {

// Constructor C78B50: a light pre-pass pointer and view count, then the shadow and
// light view/projection override parameters. Table 24D1230 appends the *Impl_
// slots that MaskedSpotLight and MaskedProjLight override.
class MaskedLight : public agl::env::EnvObj {
    SEAD_RTTI_OVERRIDE(MaskedLight, agl::env::EnvObj)
public:
    MaskedLight();
    ~MaskedLight() override;

    void initialize(int count, sead::Heap* heap) override;
    void update() override;
    void updateView(const ViewData& view, int view_index) override;
    void drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                   const sead::Matrix44f& projection, int view_index) const override;
    s32 getTypeID() const override;

    // 0x7100c79174: forwards to the implementation while enabled with a pre-pass.
    void setToLightPrePass(int index, f32 a, f32 b);

    static const agl::env::TypeInfo* sTypeInfo;

protected:
    virtual void initializeImpl_(int count, sead::Heap* heap);
    virtual void setToLightPrePassImpl_(agl::lght::LightPrePass* light_pre_pass, int index,
                                        f32 a, f32 b);
    virtual void updateImpl_();
    virtual void updateViewImpl_(const sead::Matrix34f& view, const sead::Matrix44f& projection,
                                 int view_index);
    virtual void getLightInfo_(agl::lght::LightPrePass* light_pre_pass,
                               agl::lght::LightPrePass::LightInfo* info) const;
    virtual void setShadowMapImpl_(int index, agl::lght::LightPrePass* light_pre_pass,
                                   const agl::TextureSampler* sampler,
                                   const sead::Matrix44f& matrix) const;
    virtual void drawDebugImpl_(agl::DrawContext* context, const sead::Matrix34f& view,
                                const sead::Matrix44f& projection, int view_index) const;
    virtual void genMessageMaskedLight(sead::hostio::Context* context);
    virtual void listenPropertyEventMaskedLight(const sead::hostio::PropertyEvent* event);

    agl::lght::LightPrePass* mLightPrePass = nullptr;
    void* _118 = nullptr;
    // initialize C79128 stores its count here.
    s32 mViewNum = 0;
    agl::utl::Parameter<bool> mIsEnableShadow;
    agl::utl::Parameter<bool> mIsEnablePCF;
    agl::utl::Parameter<bool> mIsEnableShadowDepthClamp;
    agl::utl::Parameter<int> mEnableShadowCtx;
    // Set to 0x100 and 0x100 by the constructor; its users are not decompiled.
    u32 _1a8 = 0x100;
    u32 _1ac = 0x100;
    agl::utl::Parameter<bool> mIsLightViewOverride;
    agl::utl::Parameter<sead::Vector3f> mLightViewTrans;
    agl::utl::Parameter<sead::Vector3f> mLightViewRotate;
    agl::utl::Parameter<bool> mIsLightProjOverride;
    agl::utl::Parameter<f32> mLightProjNear;
    agl::utl::Parameter<f32> mLightProjFar;
    agl::utl::Parameter<f32> mLightProjAspect;
    agl::utl::Parameter<f32> mLightProjFovy;
};
static_assert(sizeof(MaskedLight) == 0x2c0);

}  // namespace gsys
