#pragma once

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <common/aglTextureEnum.h>
#include <g3d/aglResTextureDataEx.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace agl {
class DrawContext;
}

namespace gsys {

// Layout from Layer's constructor 0x7100bf4378: the disposer base, a RenderBuffer at +0x20, a
// RenderTargetColor at +0x88, the dynamically allocated texture at +0x200, a ResTextureDataEx at
// +0x208 and a TextureData at +0x3d0 (its NVNtexture_ at +0x428). Layer embeds one at +0x3f0 and
// constructs the next component (RenderBuffer at +0x8e8), so the size is 0x4f8.
class LayerTexture : public sead::IDisposer {
    // CopyLayerTexture::initialize 0x7100bf5e28 allocates the texture and its GPU block.
    friend class CopyLayerTexture;

public:
    LayerTexture();
    ~LayerTexture() override;

    // 0x7100bf591c: returns the dynamic texture to the allocator and restores the default
    // texture data. Both GOT reads are the DynamicTextureAllocator and PrimitiveTexture singletons.
    void freeDynamic_();
    // 0x7100bf59ac
    void allocDynamic_(const sead::Vector2f& size, const sead::Vector2f& scale, bool flag,
                       agl::TextureFormat format);
    // 0x7100bf5af4
    void setUp_(const sead::Vector2f& size, const sead::Vector2f& scale);
    // 0x7100bf5c20
    void bind_(agl::DrawContext* draw_context);

private:
    /* 0x020 */ agl::RenderBuffer mRenderBuffer;
    /* 0x088 */ agl::RenderTargetColor mRenderTargetColor;
    /* 0x200 */ agl::TextureData* mDynamicTexture;
    /* 0x208 */ agl::g3d::ResTextureDataEx mResTextureData;
    /* 0x3d0 */ agl::TextureData mTextureData;
};
static_assert(sizeof(LayerTexture) == 0x4f8);

}  // namespace gsys
