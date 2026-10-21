#include "gsys/gsysModelSceneBuffer.h"
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelSceneContext.h"
#include "gsys/gsysGBuffer.h"
#include "gsys/gsysRenderBufferContext.h"

namespace gsys {

ModelSceneBuffer::CreateArg::CreateArg() : _0(1) {}

// 0x7100c17b60
void ModelSceneBuffer::preCalcView(ModelSceneContext* context) {
    mRenderBufferContext->clear(context->_8);
}

// 0x7100c19628
void ModelSceneBuffer::beginReducedBuffer(agl::DrawContext* draw_context,
                                          ModelSceneContext* context, bool flag) const {
    mRenderBufferContext->beginHalfBuffer(draw_context, context->_8, flag);
}

// 0x7100c19638
void ModelSceneBuffer::beginReducedQuarterBuffer(agl::DrawContext* draw_context,
                                                 ModelSceneContext* context) const {
    mRenderBufferContext->beginQuarterBuffer(draw_context, context->_8);
}

// 0x7100c19644
void ModelSceneBuffer::endReducedQuarterBuffer(agl::DrawContext* draw_context,
                                               ModelSceneContext* context) const {
    mRenderBufferContext->endQuarterBuffer(draw_context, context->_8);
}

// 0x7100c19650
void ModelSceneBuffer::endReducedBuffer(agl::DrawContext* draw_context,
                                        ModelSceneContext* context) const {
    mRenderBufferContext->endHalfBuffer(draw_context, context->_8);
}

// 0x7100c191a8
void ModelSceneBuffer::releaseOpa(const ModelSceneContext& context) const {
    mRenderBufferContext->release(context._8, 0x3e2000);
}

// 0x7100c183b0
bool ModelSceneBuffer::isZPrePassEnabled(const ModelSceneContext& context) const {
    if (!_8->isFeatureEnabled(ModelSceneConfig::Feature::ZPrePass))
        return false;
    return (context._390 >> 4) & 1;
}

// 0x7100c191bc
void ModelSceneBuffer::releaseXlu(const ModelSceneContext& context) const {
    mRenderBufferContext->release(context._8, 0x7fe60000);
    mRenderBufferContext->getContext(context._8)->mGBuffer->invalidate();
}

// 0x7100c19b44
void ModelSceneBuffer::drawDebug(agl::DrawContext*, const ModelSceneContext&) const {}

// 0x7100c19b48
void ModelSceneBuffer::attachHostIO(sead::hostio::Node*) {}

}  // namespace gsys
