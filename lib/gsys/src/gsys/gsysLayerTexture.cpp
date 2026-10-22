#include <gsys/gsysLayerTexture.h>
#include <common/aglDrawContext.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>
#include <g3d/aglTextureUtilG3D.h>
#include <gfx/seadViewport.h>
#include <utility/aglDynamicTextureAllocator.h>
#include <utility/aglPrimitiveTexture.h>

namespace gsys {

// 0x7100bf591c: return the dynamic texture to the allocator and restore the default texture data.
void LayerTexture::freeDynamic_() {
    if (!mDynamicTexture)
        return;
    agl::utl::DynamicTextureAllocator::instance()->free(mDynamicTexture);
    mDynamicTexture = nullptr;
    mTextureData = agl::utl::PrimitiveTexture::instance()->mSamplers[2]->getTextureData();
}

// 0x7100bf59ac
void LayerTexture::allocDynamic_(const sead::Vector2f& size, const sead::Vector2f& scale, bool flag,
                                 agl::TextureFormat format) {
    freeDynamic_();
    mDynamicTexture = agl::utl::DynamicTextureAllocator::instance()->allocWithoutContext(
        nullptr, "layer texture", format, u32(size.x), u32(size.y), 1, nullptr,
        agl::utl::DynamicTextureAllocator::AllocateType(!flag), false, false);
    mTextureData = *mDynamicTexture;
    setUp_(size, scale);
}

// 0x7100bf5af4
void LayerTexture::setUp_(const sead::Vector2f& size, const sead::Vector2f& scale) {
    const agl::TextureFormat format = mTextureData.getFormat();
    if (format == agl::TextureFormat::cTextureFormat_R10_G10_B10_A2_uNorm ||
        format == agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm) {
        mRenderTargetColor.applyTextureData(mTextureData, mRenderTargetColor.getMipLevel(),
                                            mRenderTargetColor.getLayer());
    }
    agl::g3d::TextureUtilG3D::convertToResTexture(&mResTextureData, mTextureData, nullptr);
    mRenderBuffer.setPhysicalArea(sead::BoundBox2f(0.0f, 0.0f, size.x, size.y));
    mRenderBuffer.setVirtualSize(sead::Vector2f(scale.x, scale.y));
}

// 0x7100bf5c20
void LayerTexture::bind_(agl::DrawContext* draw_context) {
    mRenderBuffer.bind(draw_context);
    sead::Viewport viewport(mRenderBuffer);
    viewport.apply(draw_context, mRenderBuffer);
}

}  // namespace gsys
