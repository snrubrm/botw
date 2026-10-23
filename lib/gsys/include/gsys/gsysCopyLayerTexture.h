#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <common/aglGPUMemAddr.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <common/aglTextureEnum.h>
#include <common/aglTextureSampler.h>
#include <g3d/aglResTextureDataEx.h>
#include <gfx/seadViewport.h>
#include <gsys/gsysLayerTexture.h>
#include <hostio/seadHostIONode.h>
#include <utility/aglDebugTexturePage.h>

namespace sead {
class Heap;
}

namespace agl {
class DrawContext;
}

namespace gsys {

class Layer;
class Model;

// The copy-layer texture at Graphics + 0xad8. Layout from the constructor 0x7100bf5c6c: the
// LayerTexture part (0x4f8 bytes), a hostio::Node base at +0x4f8, then the layer binding, the
// texture address/sampler/viewport used for the copy and a debug page; the allocation is
// 0x900 bytes (0x7100f2bc78). The destructor 0x7100bf5d10 releases the address at +0x510,
// cleans the debug page at +0x6c0 and destroys the LayerTexture part.
class CopyLayerTexture : public LayerTexture, public sead::hostio::Node {
public:
    CopyLayerTexture();
    ~CopyLayerTexture() override;

    enum class Format;
    enum class CopyTiming;

    // 0x7100bf5e28
    void initialize(u32 width, u32 height, Format format, sead::Heap* heap);
    // 0x7100bf5fcc: binds this texture to `layer`, keeping the layer's +0x3e8 back pointer in
    // sync and detaching it from any layer that held it before.
    void setLayer(Layer* layer);
    // 0x7100bf5ffc: copies the bound layer's viewport into mViewport.
    void adjustTrimViewportToLayer();
    // 0x7100bf6038
    void copy(agl::DrawContext* draw_context, CopyTiming timing, const agl::RenderBuffer& buffer,
              const sead::Viewport& viewport);

private:
    /* 0x500 */ Layer* mLayer;

public:
    // 0x508: stored as 0xff by the constructor and set to 1 by Graphics::sub_7100F35DE8
    // 0x7100f35de8 through the Graphics + 0xad8 pointer. Meaning unrecovered.
    u8 _508;

private:
    /* 0x509 */ u8 _509;
    u8 _50a[0x510 - 0x50a];
    /* 0x510 */ agl::GPUMemAddrBase _510;
    /* 0x528 */ agl::TextureSampler mSampler;
    /* 0x698 */ sead::Viewport mViewport;
    /* 0x6c0 */ agl::utl::DebugTexturePage mDebugTexturePage;
};
static_assert(sizeof(CopyLayerTexture) == 0x900);

}  // namespace gsys
