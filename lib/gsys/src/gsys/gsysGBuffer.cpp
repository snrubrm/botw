#include <gsys/gsysGBuffer.h>

#include <common/aglDrawContext.h>
#include <gfx/seadViewport.h>
#include <lighting/aglLightPrePass.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace gsys {

// 0x7100c7159c
bool GBuffer::isRendering() const {
    if ((mResolutionData[0].mFlags & 0x1f) != 0)
        return true;
    return (mResolutionData[1].mFlags & 0x1f) != 0;
}

// 0x7100c71e7c
void GBuffer::bindRenderBuffer(agl::DrawContext* draw_context, Resolution resolution) const {
    const agl::RenderBuffer& render_buffer = mResolutionData[int(resolution)].mRenderBuffer;
    render_buffer.bind(draw_context);
    sead::Viewport viewport(render_buffer);
    viewport.apply(draw_context, render_buffer);
}

// NON_MATCHING: same 48 bytes, but clang keeps the two indices in different registers and
// scales the second one with a separate lsl where the original folds it into the load.
// 0x7100c7256c
void GBuffer::swapRenderTarget() {
    agl::RenderBuffer& buffer = mResolutionData[0].mRenderBuffer;
    agl::RenderTargetColor* target = buffer.getRenderTargetColor(mBufferRecords[3]._190);
    buffer.setRenderTargetColor(buffer.getRenderTargetColor(mBufferRecords[0]._190),
                                mBufferRecords[3]._190);
    buffer.setRenderTargetColor(target, mBufferRecords[0]._190);
}

// 0x7100c737a8
void GBuffer::invalidatePreShading(PreShadingBufferType type) {
    PreShadingBuffer& buffer = mPreShadingBuffers[int(type)];
    if (buffer.mTexture) {
        agl::utl::DynamicTextureAllocator::instance()->free(buffer.mTexture);
        buffer.mTexture = nullptr;
    }
    if (type == PreShadingBufferType(0) && mLightPrePass) {
        mLightPrePass->release(mLightPrePassView);
        mLightPrePass = nullptr;
        mLightPrePassView = -1;
    }
    _9 &= ~(1 << int(type));
}

// 0x7100c7367c
void GBuffer::beginDeferredShading(agl::DrawContext* draw_context, MaterialIdMask mask,
                                   agl::TextureCompSel comp_sel) {
    mResolutionData[0].mRenderBuffer.setRenderTargetColorNullAll();
    mResolutionData[0].mRenderBuffer.setRenderTargetColor(&mDeferredColorTarget, 0);
    mResolutionData[0].mRenderBuffer.setRenderTargetDepth(nullptr);

    if ((mResolutionData[0].mFlags & 4) != 0) {
        expandMaterialID_(draw_context, Resolution(0), mask, comp_sel);
        return;
    }

    mResolutionData[0].mRenderBuffer.bind(draw_context);
    sead::Viewport viewport(mResolutionData[0].mRenderBuffer);
    viewport.apply(draw_context, mResolutionData[0].mRenderBuffer);
}

// 0x7100c73734
// NON_MATCHING: the zero GPUMemVoidAddr's middle field is stored 8 bytes wide
// (`str xzr` at +0x1f30) where the original has the 4-byte `str wzr`.
void GBuffer::endDeferredShading() {
    if (!mExpandMaterialIdTexture)
        return;

    agl::utl::DynamicTextureAllocator::instance()->free(mExpandMaterialIdTexture);
    mExpandMaterialIdTexture = nullptr;
    mDeferredDepthTarget.setStorage(agl::GPUMemVoidAddr());
}

// 0x7100c7158c
void GBuffer::setMaterialIdMask(MaterialIdMask mask, u8 value) {
    mMaterialIdMasks[int(mask)] = value;
}

// 0x7100c72f08
void GBuffer::forwardPreShadingStepForXlu(agl::DrawContext* draw_context, int) {
    expandMaterialID_(draw_context, Resolution(1), MaterialIdMask(2), agl::TextureCompSel(2));
}

// 0x7100c73cf4
void GBuffer::entryToDebugTexturePagePreShading(agl::DrawContext*, int,
                                                const agl::utl::DebugTexturePage*) {}

// 0x7100c73af4
void GBuffer::setFormat(BufferType type, agl::TextureFormat format) {
    mBufferRecords[int(type)].mFormat = format;
}

// 0x7100c73b30
void GBuffer::setReduceFilter(BufferType type, agl::TextureFilterType filter) {
    mBufferRecords[int(type)].mReduceFilter = u32(filter);
}

// 0x7100c7259c
void GBuffer::setClearColor(BufferType type, bool enable, const sead::Color4f& color) {
    BufferRecord& record = mBufferRecords[int(type)];
    record.mFlags = enable ? record.mFlags | 1 : record.mFlags & ~1;
    record.mClearColor = color;
}

// 0x7100c73b04
void GBuffer::enableMEM2(BufferType type, bool enable) {
    u8& flags = mBufferRecords[int(type)].mFlags;
    flags = enable ? flags | 2 : flags & ~2;
}

}
