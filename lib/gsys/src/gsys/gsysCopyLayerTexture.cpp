#include <gsys/gsysCopyLayerTexture.h>
#include <basis/seadNew.h>
#include <common/aglDrawContext.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglGPUCommon.hpp>
#include <detail/aglPrivateResource.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadViewport.h>
#include <gsys/gsysLayer.h>
#include <gsys/gsysORUtil.h>
#include <math/seadMathCalcCommon.h>
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglImageFilter2D.h>

namespace gsys {

// Only reader of the byte at 0x71025fcce0 (copy()'s early-out); it has no writer in the
// executable. Meaning unrecovered. Hidden: the original reaches it with a direct adrp + ldrb.
__attribute__((visibility("hidden"))) bool sUnk_71025fcce0;

// NON_MATCHING: the two GPU address temporaries get separate 0x18-byte stack slots; the original
// reuses one (the frame is 0x10 larger). Calls, stores and the format table match.
// 0x7100bf5e28
void CopyLayerTexture::initialize(u32 width, u32 height, Format format, sead::Heap* heap) {
    static const agl::TextureFormat sFormats[] = {
        agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm,
        agl::TextureFormat::cTextureFormat_R10_G10_B10_A2_uNorm,
        agl::TextureFormat::cTextureFormat_BC1_uNorm,
        agl::TextureFormat::cTextureFormat_BC3_uNorm,
    };
    mTextureData.initialize_(agl::TextureType::cTextureType_2D, sFormats[u32(format)], width,
                             height, 1, 1, agl::TextureAttribute(0), agl::MultiSampleType(0),
                             true);

    const u32 size = mTextureData.getImageByteSize();
    auto* block = new (heap) agl::GPUMemBlock<u8>;
    block->allocBuffer_(size, heap, 0x2000, agl::MemoryAttribute::Default);
    _510 = agl::GPUMemAddrBase(*block, 0);
    _510.flushCPUCache(mTextureData.getImageByteSize());
    const agl::GPUMemVoidAddr image(_510);
    mTextureData.setImagePtr(image, 0);

    const sead::Vector2f viewport{f32(width), f32(height)};
    setUp_(viewport, viewport);

    // Discarded in the original: the compressed-format test has no branch here.
    mTextureData.isCompressedFormat();

    sead::Heap* debug_heap = agl::detail::PrivateResource::instance()->getDebugHeap();
    mDebugTexturePage.setUp(1, "CopyLayerTexture", debug_heap);
    ORUtil::setNodeMeta(this, ORUtil::Category::_4, "rndr_FaderLayer", debug_heap);
}

// 0x7100bf5d10
CopyLayerTexture::~CopyLayerTexture() {
    if (_510.isValid())
        _510.deleteGPUMemBlock();
}

// 0x7100bf5fcc: binds this texture to `layer`; both ends of the association are cleared and
// replaced. The Layer back pointer is at +0x3e8, this object's at +0x500.
void CopyLayerTexture::setLayer(Layer* layer) {
    if (mLayer == layer)
        return;
    if (mLayer)
        mLayer->mCopyLayerTexture = nullptr;
    if (layer) {
        if (layer->mCopyLayerTexture)
            layer->mCopyLayerTexture->mLayer = nullptr;
        layer->mCopyLayerTexture = this;
    }
    mLayer = layer;
}

// 0x7100bf5ffc: the trim viewport follows the layer's viewport.
void CopyLayerTexture::adjustTrimViewportToLayer() {
    if (!mLayer)
        return;
    mViewport = mLayer->mViewport;
}

// 0x7100bf6038: renders the compressed layer texture through a temporary uncompressed render
// target, then compresses the target back into mTextureData.
bool CopyLayerTexture::copy(agl::DrawContext* draw_context, CopyTiming timing,
                            const agl::RenderBuffer& buffer, const sead::Viewport& viewport) {
    if (_508 != s32(timing) || sUnk_71025fcce0)
        return false;

    mTextureData.forceChangeSRGBToUNorm();
    mSampler.applyTextureData(*buffer.getRenderTargetColor(0));

    agl::utl::DynamicTextureAllocator* allocator = agl::utl::DynamicTextureAllocator::instance();
    agl::TextureData* temporary = nullptr;
    if (mTextureData.isCompressedFormat()) {
        const sead::SafeString name("copy_temp");
        const u32 width = sead::Mathu::max(mTextureData.getWidth(), 1u);
        const u32 height =
            sead::Mathi::max(mTextureData.getMinHeight_(), mTextureData.getHeight());
        temporary = allocator->alloc(
            draw_context, name, agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, width,
            height, 1, nullptr, agl::utl::DynamicTextureAllocator::AllocateType(0), true, false);

        // The temporary takes over the colour target's texture state; layer and mip level stay.
        agl::RenderTargetColor* target = mRenderBuffer.getRenderTargetColor(0);
        target->applyTextureData(*temporary, target->getMipLevel(), target->getLayer());
    }

    mRenderBuffer.bind(draw_context);
    const sead::Viewport target_viewport(mRenderBuffer);
    target_viewport.apply(draw_context, mRenderBuffer);

    sead::GraphicsContext graphics_context;
    graphics_context.setBlendEnable(false, 0);
    graphics_context.setDepthTestEnable(false);
    graphics_context.setDepthWriteEnable(false);
    graphics_context.apply(draw_context);

    const sead::BoundBox2f& area = buffer.getPhysicalArea();
    const f32 area_width = area.getMax().x - area.getMin().x;
    const f32 area_height = area.getMax().y - area.getMin().y;
    sead::Vector2f frame_size;
    mViewport.getOnFrameBufferSize(&frame_size, buffer);
    sead::Vector2f frame_pos;
    mViewport.getOnFrameBufferPos(&frame_pos, buffer);

    const sead::Vector2f uv_size(frame_size.x / area_width, frame_size.y / area_height);
    const sead::Vector2f uv_pos(
        0.5f - (0.5f - frame_pos.x / area_width) / uv_size.x,
        -(0.5f - (0.5f - frame_pos.y / area_height) / uv_size.y));

    const f32 scale_x =
        f32(sead::Mathu::max(mTextureData.getWidth(), 1u)) /
        f32(sead::Mathu::max(mSampler.getTextureData().getWidth(), 1u));
    // The original converts each signed height maximum to unsigned before the second call.
    const f32 scale_y_num =
        f32(u32(sead::Mathi::max(mTextureData.getMinHeight_(), mTextureData.getHeight())));
    const f32 scale_y_den = f32(u32(sead::Mathi::max(
        mSampler.getTextureData().getMinHeight_(), mSampler.getTextureData().getHeight())));
    const f32 scale_y = scale_y_num / scale_y_den;
    const sead::Vector2f tex_scale(scale_x, scale_y);

    agl::utl::ImageFilter2D::drawTextureTexCoord(draw_context, mSampler, target_viewport, uv_size,
                                                 0.0f, uv_pos, tex_scale, sead::Vector2f::zero);
    _508 = 0xff;

    if (temporary) {
        temporary->compressToAll(draw_context, &mTextureData);
        allocator->free(temporary);
    }
    if (_509)
        mTextureData.forceChangeUNormToSRGB();

    buffer.bind(draw_context);
    viewport.apply(draw_context, buffer);
    return true;
}

}  // namespace gsys
