#include <gsys/gsysCopyLayerTexture.h>
#include <basis/seadNew.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglGPUCommon.hpp>
#include <detail/aglPrivateResource.h>
#include <gsys/gsysLayer.h>
#include <gsys/gsysORUtil.h>

namespace gsys {

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
    _510.flushCPUCache(size);
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

}  // namespace gsys
