#pragma once

#include "gsys/gsysModelSceneComponent.h"

namespace agl {
class DrawContext;
class TextureData;
}

namespace agl::pfx {
class AutoExposure;
class Bloom;
class ColorCorrection;
class DepthOfField;
class FlareFilter;
class GlareFilter;
class HDRCompose;
}  // namespace agl::pfx

namespace sead::hostio {
class Node;
}

namespace gsys {

class ModelSceneContext;
class ModelSceneGI;

// Partial: the hostio hook, the post-effect enable tests and the passes that only forward to the
// post effects are modelled. The rest of the component (D1 0x7100c35518, initialize 0x7100c3565c,
// calc 0x7100c35904, ...) is still undecompiled. The destructor is declared only so this file does
// not emit the class vtable.
class ModelScenePfx : public ModelSceneComponent {
public:
    // Partial: only the default value at +0 is known (0x7100c35494).
    struct CreateArg {
        CreateArg();
        u32 _0 = 1;
    };

    ~ModelScenePfx() override;
    // 0x7100c36538: the component attaches no hostio node of its own.
    void attachHostIO(sead::hostio::Node* node) override;

    // 0x7100c35a98: the HDR feature must be enabled and the compose object created.
    bool isHDRComposeEnabled() const;
    // 0x7100c35abc: the correction object must exist and the feature be enabled.
    bool isColorCorrectionEnabled() const;
    // 0x7100c35ae0: the bloom object must exist and its buffer cover the view (-1 for any).
    bool isBloomEnabled(int view) const;

    // 0x7100c35e9c: the depth-of-field pass draws with the view's depth target.
    void drawDOF(agl::DrawContext* draw_context, ModelSceneContext* context,
                 const agl::TextureData* texture) const;
    // 0x7100c362e0 / 0x7100c3627c: the auto-exposure pass and the per-view buffer release.
    void drawAutoExposure(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    void release(int view) const;
    // 0x7100c35f1c / 0x7100c35f8c: the filter draws pick the bloom-buffer path when the view
    // has one.
    void drawGlareFilter(agl::DrawContext* draw_context, const ModelSceneContext& context) const;
    void drawFlareFilter(agl::DrawContext* draw_context, const ModelSceneContext& context,
                         const agl::TextureData& texture) const;
    // 0x7100c36310: each created effect draws its own debug view.
    void drawDebug(agl::DrawContext* draw_context, const ModelSceneContext& context) const override;
    // 0x7100c363a4 / 0x7100c36404 / 0x7100c36458: the GPU passes of the post effects.
    void calcGPU();
    void calcViewGPU(const ModelSceneContext& context) override;
    void calcGPUDrawBackGround() const;
    // 0x7100c364bc: the per-view background passes of bloom and HDR compose.
    void calcGPUDrawBackGround(ModelSceneContext* context) const;
    // 0x7100c35904: updates the HDR compose flags and calculates the enabled post effects.
    void calc(const ModelSceneGI& gi, f32, bool flag);
    // 0x7100c3600c: the bloom pass with the view's depth texture.
    void drawBloom(agl::DrawContext* draw_context, ModelSceneContext* context,
                   const agl::TextureData* texture) const;

private:
    /* 0x250 */ u8 _250[0x280 - 0x250];
    // Initialised to 1 by the constructor 0x7100c354a0; drawBloom reads bit 0 to pick the
    // bloom-buffer draw when HDR compose is enabled.
    /* 0x280 */ u32 mFlags;
    /* 0x284 */ u32 _284;

    // The post effects the component releases in release(int); the rest of the member block stays
    // unmodelled.
    /* 0x288 */ agl::pfx::Bloom* mBloom;
    /* 0x290 */ u8 _290[0x298 - 0x290];
    /* 0x298 */ agl::pfx::DepthOfField* mDepthOfField;
    /* 0x2a0 */ agl::pfx::AutoExposure* mAutoExposure;
    /* 0x2a8 */ agl::pfx::ColorCorrection* mColorCorrection;
    /* 0x2b0 */ agl::pfx::GlareFilter* mGlareFilter;
    /* 0x2b8 */ agl::pfx::FlareFilter* mFlareFilter;
    /* 0x2c0 */ agl::pfx::HDRCompose* mHDRCompose;
};

}  // namespace gsys
