#include "gsys/gsysModelSceneBuffer.h"
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelSceneContext.h"
#include "gsys/gsysGBuffer.h"
#include "gsys/gsysRenderBufferContext.h"

namespace gsys {

ModelSceneBuffer::CreateArg::CreateArg() : _0(1) {}

// 0x7100c17b60
void ModelSceneBuffer::preCalcView(ModelSceneContext* context) {
    mRenderBufferContext->clear(context->getViewIndex());
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

// 0x7100c191a8
void ModelSceneBuffer::releaseOpa(const ModelSceneContext& context) const {
    mRenderBufferContext->release(context.getViewIndex(), 0x2003e);
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
    return (context._390 >> 4) & 1;
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
