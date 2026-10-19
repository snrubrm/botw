#include <gsys/gsysModelRenderContext.h>
#include <gsys/gsysShaderContext.h>

#include <common/aglRenderBuffer.h>
#include <gfx/seadViewport.h>

namespace gsys {

void ModelRenderContext::setPolygonOffset(ModelEnum::PolygonOffsetType type, f32 a, f32 b) {
    FloatPair& pair = mUnk2d0[int(type)];
    pair._4 = a;
    pair._0 = b;
}


ModelRenderContext::CreateArg::CreateArg() : _0(8), viewCount(1) {}

void ModelRenderContext::initialize(const CreateArg& arg, sead::Heap* heap) {
    mShaderContext = new (heap) ShaderContext;
    mShaderContext->initialize(arg._0, arg.viewCount, heap);
    mViewData.tryAllocBuffer(arg.viewCount, heap, 16);
    for (auto& pair : mUnk2d0) {
        pair._0 = 0;
        pair._4 = 0;
    }
}

// NON_MATCHING: buffer bounds selection and loop-count reload differ.
void ModelRenderContext::calcGPU(bool flag) const {
    for (int i = 0; i < mViewData.size(); ++i) {
        const ViewData& view = mViewData[i];
        mShaderContext->calcGpuViewFlush(i, view.view, view.frustum.getProjectionMatrix(),
                                       view.frustum, false, flag);
    }
}

// 0x7100c0887c
void ModelRenderContext::bind(sead::DrawContext* draw_context) const {
    if (mRenderBuffer) {
        mRenderBuffer->bind(draw_context);
        return mViewport->apply(draw_context, *mRenderBuffer);
    }
}

void ModelRenderContext::pushPassTexture(PassTextureType type, const agl::TextureData* texture) {
    const agl::TextureData* previous = mPassTextures[type];
    mPassTextures[type] = texture;
    mSavedPassTextures[type] = previous;
}

void ModelRenderContext::popPassTexture(PassTextureType type) {
    if (mSavedPassTextures[type]) {
        mPassTextures[type] = mSavedPassTextures[type];
        mSavedPassTextures[type] = nullptr;
    }
}

}  // namespace gsys
