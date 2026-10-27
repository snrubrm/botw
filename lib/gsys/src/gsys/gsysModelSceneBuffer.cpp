#include "gsys/gsysModelSceneBuffer.h"
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelSceneContext.h"
#include "gsys/gsysGPUStressAnalyzer.h"
#include "gsys/gsysGBuffer.h"
#include "gsys/gsysRenderBufferContext.h"

namespace gsys {

// The per-frame step the GPU stress adjustors apply (0x7101da2618 in the original). Kept in
// this TU so the adjustors' loads are not folded into an immediate.
__attribute__((visibility("hidden"))) const f32 sUnk_7101da2618 = -0.01f;

ModelSceneBuffer::CreateArg::CreateArg() : _0(1) {}

// 0x7100c17b60
void ModelSceneBuffer::preCalcView(ModelSceneContext* context) {
    mRenderBufferContext->clear(context->getViewIndex());
}

// 0x7100c18ee4
void ModelSceneBuffer::beginDeferredShading(agl::DrawContext* draw_context,
                                            ModelSceneContext* context) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context->getViewIndex())->mGBuffer;
    gbuffer->beginDeferredShading(draw_context, GBuffer::MaterialIdMask(0),
                                  agl::TextureCompSel(2));
    context->setRenderBuffer(gbuffer->getRenderBuffer());
}

// 0x7100c18f3c
bool ModelSceneBuffer::isDeferredShadingValid(const ModelSceneContext& context) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::DeferredShading))
        return false;
    if (_1718 < 1)
        return false;
    return context.isQueueMaskValid(ModelSceneContext::QueueType(1), sead::BitFlag32(0x2000));
}

// 0x7100c18fa4
bool ModelSceneBuffer::isPreDeferredShadingValid(const ModelSceneContext& context) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::DeferredShading))
        return false;
    if (_1718 < 1)
        return false;
    return context.isQueueMaskValid(ModelSceneContext::QueueType(1), sead::BitFlag32(0x1000));
}

// 0x7100c17b6c
void ModelSceneBuffer::updateFrame() {
    mFrameRateControlBuffer.updateFrame();
}

// 0x7100c19628
void ModelSceneBuffer::beginReducedBuffer(agl::DrawContext* draw_context,
                                          ModelSceneContext* context, bool flag) const {
    mRenderBufferContext->beginHalfBuffer(draw_context, context->getViewIndex(), flag);
}

// 0x7100c19638
void ModelSceneBuffer::beginReducedQuarterBuffer(agl::DrawContext* draw_context,
                                                 ModelSceneContext* context) const {
    mRenderBufferContext->beginQuarterBuffer(draw_context, context->getViewIndex());
}

// 0x7100c19644
void ModelSceneBuffer::endReducedQuarterBuffer(agl::DrawContext* draw_context,
                                               ModelSceneContext* context) const {
    mRenderBufferContext->endQuarterBuffer(draw_context, context->getViewIndex());
}

// 0x7100c19650
void ModelSceneBuffer::endReducedBuffer(agl::DrawContext* draw_context,
                                        ModelSceneContext* context) const {
    mRenderBufferContext->endHalfBuffer(draw_context, context->getViewIndex());
}

// 0x7100c183d0
void ModelSceneBuffer::drawGBufferOpa(agl::DrawContext* draw_context,
                                      const ModelSceneContext& context) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context.getViewIndex())->mGBuffer;
    ModelRenderContext::DrawArg arg("Model(GBuffer/Opa+AlphaMask)",
                                    *context.getRenderQueue(ModelSceneContext::QueueType(0)),
                                    sead::BitFlag32(0x10), ModelEnum::ShaderAssignType(2), 0,
                                    0x21, 0xffff);
    arg._40 = 4;
    arg._30 = gbuffer->getMaterialIdMask();
    arg._34 = gbuffer->getBlendMaskMaybe();
    arg._44 = 3;
    context.draw(draw_context, arg);
}

// 0x7100c190e8
void ModelSceneBuffer::invalidateGBufferPreShading(ModelSceneContext* context,
                                                  const ModelSceneGI&) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context->getViewIndex())->mGBuffer;
    context->popPassTexture(ModelRenderContext::PassTextureType(4));
    gbuffer->invalidatePreShading(GBuffer::PreShadingBufferType(2));
    context->popPassTexture(ModelRenderContext::PassTextureType(0x16));
    gbuffer->invalidatePreShading(GBuffer::PreShadingBufferType(3));
    context->popPassTexture(ModelRenderContext::PassTextureType(5));
    gbuffer->invalidatePreShading(GBuffer::PreShadingBufferType(0));
    context->popPassTexture(ModelRenderContext::PassTextureType(7));
    gbuffer->invalidatePreShading(GBuffer::PreShadingBufferType(4));
    context->popPassTexture(ModelRenderContext::PassTextureType(0x10));
    gbuffer->invalidatePreShading(GBuffer::PreShadingBufferType(5));
}

// NON_MATCHING: same 25 instructions and size; clang if-converts the two early returns into
// selects where the original keeps tbnz branches.
// 0x7100c19ae0
const agl::TextureData* ModelSceneBuffer::selectBloomDepth(int view) const {
    const RenderBufferContext::Context* context = mRenderBufferContext->getContext(view);
    const agl::TextureData* depth = &context->_c98;
    if ((_1710 & 8) == 0)
        return depth;
    const u32 flags = context->mPassFlagsMaybe;
    if ((flags & 0x800) != 0)
        return &context->_1a68;
    if ((flags & 1) != 0)
        return &context->_e08;
    return (flags & 0x1000) != 0 ? depth : &context->_18f8;
}

// 0x7100c191a8
void ModelSceneBuffer::releaseOpa(const ModelSceneContext& context) const {
    mRenderBufferContext->release(context.getViewIndex(), 0x2003e);
}

// 0x7100c184a8
void ModelSceneBuffer::drawGBufferXluSeal(agl::DrawContext* draw_context,
                                          const ModelSceneContext& context) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context.getViewIndex())->mGBuffer;
    gbuffer->bindRenderBuffer(draw_context, GBuffer::Resolution(0));
    ModelRenderContext::DrawArg arg("Model(GBuffer/XluSeal)",
                                    *context.getRenderQueue(ModelSceneContext::QueueType(1)),
                                    sead::BitFlag32(0x200), ModelEnum::ShaderAssignType(2), 0, 0x30,
                                    0xffff);
    arg._40 = 5;
    arg._30 = gbuffer->getMaterialIdMaskXluSealMaybe();
    arg._34 = gbuffer->getBlendMaskXluSealMaybe();
    arg._44 = 3;
    context.draw(draw_context, arg);
}

// NON_MATCHING: 276 bytes against 272; the target stores DrawArg +0x4c and +0x48 separately,
// clang merges them into one stp in every natural assignment order tried.
// 0x7100c187a4
void ModelSceneBuffer::drawGBufferXluOpa(agl::DrawContext* draw_context,
                                         const ModelSceneContext& context) const {
    if (!context.isQueueMaskValid(ModelSceneContext::QueueType(1), sead::BitFlag32(0x40)))
        return;
    GBuffer* gbuffer = mRenderBufferContext->getContext(context.getViewIndex())->mGBuffer;
    gbuffer->swapRenderTarget();
    gbuffer->bindRenderBuffer(draw_context, GBuffer::Resolution(0));
    ModelRenderContext::DrawArg arg("Model(GBuffer/XluOpa)",
                                    *context.getRenderQueue(ModelSceneContext::QueueType(1)),
                                    sead::BitFlag32(0x40), ModelEnum::ShaderAssignType(2), 0,
                                    0x20020, 0xffff);
    arg._40 = 7;
    arg._30 = 0xff;
    arg._34 = gbuffer->getBlendMaskXluSealMaybe();
    arg._44 = 3;
    context.draw(draw_context, arg);
    gbuffer->swapRenderTarget();
}

// 0x7100c18c64
void ModelSceneBuffer::drawGBufferXlu(agl::DrawContext* draw_context, ModelSceneContext* context,
                                      bool) const {
    if (!context->isQueueMaskValid(ModelSceneContext::QueueType(1), sead::BitFlag32(0x20)))
        return;
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::Xlu))
        return;
    GBuffer* gbuffer = mRenderBufferContext->getContext(context->getViewIndex())->mGBuffer;
    gbuffer->bindRenderBuffer(draw_context, GBuffer::Resolution(0));
    ModelRenderContext::DrawArg arg("Model(GBuffer/Xlu)",
                                    *context->getRenderQueue(ModelSceneContext::QueueType(1)),
                                    sead::BitFlag32(0x20), ModelEnum::ShaderAssignType(2), 0, 0,
                                    0xffff);
    arg._40 = 8;
    arg._30 = gbuffer->getMaterialIdMaskXluSealMaybe();
    arg._34 = gbuffer->getBlendMaskXluSealMaybe();
    context->draw(draw_context, arg);
}

// 0x7100c18c00
void ModelSceneBuffer::endGBufferPreShading(agl::DrawContext* draw_context,
                                            ModelSceneContext* context) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context->getViewIndex())->mGBuffer;
    if (_1712 & 8)
        gbuffer->entryToDebugTexturePagePreShading(draw_context, context->getViewIndex(), &mDebugTexturePage);
    gbuffer->endPreShading(draw_context);
}

// 0x7100c18d70
void ModelSceneBuffer::expandGBuffer(agl::DrawContext* draw_context,
                                     ModelSceneContext* context) const {
    GBuffer* gbuffer = mRenderBufferContext->getContext(context->getViewIndex())->mGBuffer;
    gbuffer->expand(draw_context);
    if (_1712 & 4)
        gbuffer->entryToDebugTexturePage(draw_context, context->getViewIndex(), &mDebugTexturePage);
    expandDepthBuffer(draw_context, context);
}

// 0x7100c183b0
bool ModelSceneBuffer::isZPrePassEnabled(const ModelSceneContext& context) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::ZPrePass))
        return false;
    return (context.mFlags >> 4) & 1;
}

// 0x7100c1900c
void ModelSceneBuffer::drawDeferredShading(agl::DrawContext* draw_context,
                                           ModelSceneContext* context) const {
    context->drawQueue(draw_context, "Model(Deferred Shading)", ModelSceneContext::QueueType(1),
                       sead::BitFlag32(0x2000), 0, ModelEnum::ShaderAssignType(0),
                       ModelSceneContext::ViewProjType(0), 0, 0xffff);
}

// 0x7100c191bc
void ModelSceneBuffer::releaseXlu(const ModelSceneContext& context) const {
    mRenderBufferContext->release(context.getViewIndex(), 0x607fe);
    mRenderBufferContext->getContext(context.getViewIndex())->mGBuffer->invalidate();
}

// 0x7100c19b44
void ModelSceneBuffer::drawDebug(agl::DrawContext*, const ModelSceneContext&) const {}

// 0x7100c19b48
void ModelSceneBuffer::attachHostIO(sead::hostio::Node*) {}

}  // namespace gsys
