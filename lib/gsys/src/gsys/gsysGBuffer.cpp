#include <gsys/gsysGBuffer.h>

#include <common/aglDrawContext.h>
#include <gfx/seadViewport.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace gsys {

// 0x7100c7367c
void GBuffer::beginDeferredShading(agl::DrawContext* draw_context, MaterialIdMask mask,
                                   agl::TextureCompSel comp_sel) {
    mRenderBuffer.setRenderTargetColorNullAll();
    mRenderBuffer.setRenderTargetColor(&mDeferredColorTarget, 0);
    mRenderBuffer.setRenderTargetDepth(nullptr);

    if ((mFlags768 & 4) != 0) {
        expandMaterialID_(draw_context, Resolution(0), mask, comp_sel);
        return;
    }

    mRenderBuffer.bind(draw_context);
    sead::Viewport viewport(mRenderBuffer);
    viewport.apply(draw_context, mRenderBuffer);
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
