#pragma once

#include <basis/seadTypes.h>
#include "factory/aglFrameRateControlBuffer.h"
#include "gsys/gsysModelSceneComponent.h"

namespace gsys {
class ModelSceneGI;
class RenderBufferContext;

// ModelScene constructs this component at +0x3778, before the next component
// at +0x4ea0. C17558 initializes its owned context pointer; C176EC creates it.
class ModelSceneBuffer : public ModelSceneComponent {
public:
    // Constructor 0x7100c1754c stores 1 in the first word; initialize 0x7100c176ec takes it.
    struct CreateArg {
        CreateArg();

        s32 _0;
    };

    ModelSceneBuffer();
    ~ModelSceneBuffer() override;

    // Inline-only accessor name: Graphics F34F1C reads this pointer through the scene.
    RenderBufferContext* getRenderBufferContext() const { return mRenderBufferContext; }

    // 0x7100c17b60 / 0x7100c19628 .. 0x7100c19650: the view switches, forwarded to the
    // render buffer context with the context's view byte.
    void preCalcView(ModelSceneContext* context) override;
    // 0x7100c17b6c: forwards to the frame rate control buffer at +0x258.
    void updateFrame();
    void beginReducedBuffer(agl::DrawContext* draw_context, ModelSceneContext* context,
                            bool flag) const;
    void beginReducedQuarterBuffer(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    void endReducedQuarterBuffer(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    void endReducedBuffer(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    // 0x7100c18ee4: begins the deferred pass of the context's GBuffer.
    void beginDeferredShading(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    // 0x7100c18f3c / 0x7100c18fa4
    bool isDeferredShadingValid(const ModelSceneContext& context) const;
    bool isPreDeferredShadingValid(const ModelSceneContext& context) const;
    // 0x7100c1900c: draws the deferred-shading queue into the context.
    void drawDeferredShading(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    // 0x7100c191a8 / 0x7100c191bc
    void releaseOpa(const ModelSceneContext& context) const;
    void releaseXlu(const ModelSceneContext& context) const;
    // 0x7100c183b0
    bool isZPrePassEnabled(const ModelSceneContext& context) const;
    // 0x7100c18c00 / 0x7100c18d70 / 0x7100c18df4
    void endGBufferPreShading(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    void expandGBuffer(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    void expandDepthBuffer(agl::DrawContext* draw_context, ModelSceneContext* context) const;
    // 0x7100c190e8: frees the pre-shading buffers of the context's GBuffer.
    void invalidateGBufferPreShading(ModelSceneContext* context, const ModelSceneGI& gi) const;
    // 0x7100c19b44 / 0x7100c19b48: the buffer draws no debug output and attaches nothing.
    void drawDebug(agl::DrawContext* draw_context, const ModelSceneContext& context) const override;
    void attachHostIO(sead::hostio::Node* node) override;

private:
    RenderBufferContext* mRenderBufferContext;
    // Constructor C17558 constructs the frame rate controller at +0x258 and the AA filter at
    // +0x4b8, so the controller is 0x260 bytes.
    agl::fctr::FrameRateControlBuffer mFrameRateControlBuffer;
    u8 _4b8[0x1712 - 0x4b8];
    // endGBufferPreShading tests bit 3, expandGBuffer bit 2.
    u8 _1712;
    u8 _1713[0x1718 - 0x1713];
    // 0x7100c18f3c / 0x7100c18fa4 require at least one of these records.
    s32 _1718;
    u8 _171c[0x1728 - 0x171c];
};
static_assert(sizeof(ModelSceneBuffer) == 0x1728);

}  // namespace gsys
