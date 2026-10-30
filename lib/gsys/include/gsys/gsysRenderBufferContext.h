#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>
#include <gfx/seadViewport.h>
#include <hostio/seadHostIONode.h>
#include <cstddef>

namespace agl {
class DrawContext;
}

namespace gsys {
class GBuffer;

// Owned by ModelSceneBuffer at +0x250. initialize C176EC allocates 0xc0 bytes,
// invokes C5902C, then initializes the per-view array through C5934C.
// C5902C installs AP 24CF7C0, whose first slot is Node::getNodeClassType 7D1F0C,
// followed by the C590D4/C59274 destructors.
class RenderBufferContext : public sead::hostio::Node {
public:
    // The per-view GPU buffers, constructed and destroyed as 0xc60-byte records.
    class BufferData {
    public:
        BufferData();
        ~BufferData();
        void enableHiZ(bool enable);

        agl::RenderBuffer mRenderBuffer;
        agl::RenderTargetColor mColorTarget0;
        agl::RenderTargetColor mColorTarget1;
        agl::RenderTargetColor mColorTarget2;
        agl::RenderTargetDepth mDepthTarget;
        agl::TextureData* mTexture0 = nullptr;
        agl::TextureData* mHiZTexture = nullptr;
        agl::TextureData* mTexture2 = nullptr;
        agl::TextureSampler mSampler0;
        agl::TextureSampler mSampler1;
        agl::TextureSampler mSampler2;
        agl::TextureSampler mSampler3;
        agl::GPUMemVoidAddr mHiZAddr;
        sead::Viewport mViewport;
    };
    static_assert(sizeof(BufferData) == 0xc60);

    struct Context {
        Context();
        ~Context();
        u32 _0 = 0;
        // Pass flags written by the view's draw record.
        u32 mPassFlagsMaybe = 0;
        u32 _8 = 0;
        sead::Viewport _10;
        agl::RenderBuffer _38;
        agl::RenderTargetColor _a0;
        agl::TextureData _218;
        agl::TextureSampler _340;
        u8 _4b0[8];
        BufferData _4b8;
        BufferData _1118;
        BufferData _1d78;
        agl::RenderBuffer _29d8;
        agl::RenderTargetColor _2a40;
        u8 _2bb8[8];
        agl::TextureSampler _2bc0;
        sead::Viewport _2d30;
        agl::RenderBuffer _2d58;
        agl::RenderTargetColor _2dc0;
        u8 _2f38[8];
        agl::TextureSampler _2f40;
        sead::Viewport _30b0;
        u8 _30d8[8];
        agl::TextureData _30e0;
        // Per-axis render scale, written by C5934C and read by update C59684.
        f32 _3208;
        f32 _320c;
        GBuffer* mGBuffer;
        agl::UniformBlock _3218;
        u8 _3290[8];
        agl::RenderTargetColor _3298;
        agl::TextureSampler _3410;
        u8 _3580[8];
        agl::RenderTargetColor _3588;
        agl::TextureSampler _3700;
        u8 _3870[8];
    };
    static_assert(sizeof(Context) == 0x3878);
    static_assert(offsetof(Context, mGBuffer) == 0x3210);

    RenderBufferContext();
    virtual ~RenderBufferContext();

    // Inline-only name: F34F1C and the scene buffer operations use this Buffer's
    // unsigned index fallback to element zero.
    Context* getContext(u32 index) { return &mContexts[index]; }
    const Context* getContext(u32 index) const { return &mContexts[index]; }

    // Declared only; the ModelSceneBuffer view switches tail-call these.
    void clear(int index);
    void beginHalfBuffer(agl::DrawContext* context, int index, bool flag);
    void beginQuarterBuffer(agl::DrawContext* context, int index);
    void endQuarterBuffer(agl::DrawContext* context, int index);
    void endHalfBuffer(agl::DrawContext* context, int index);
    void release(int index, u32 mask);

    // Item-filter mode of the first scene's render buffer: update 0x7101293fc0 stores 10 or 1.
    void setItemFilterMode(s32 mode) { mItemFilterMode = mode; }
    s32 getItemFilterMode() const { return mItemFilterMode; }

private:
    sead::Buffer<Context> mContexts;
    u8 _18[0x38 - 0x18];
    // Item-filter mode write by the update 0x7101293fc0 through the ModelSceneBuffer pointer
    // (ModelScene +0x39c8): 10 for a running filter, 1 when the filter is inactive. The update
    // reads the first scene's +0x5da4 alpha and the byte at RenderBufferContext+0xc.
    /* 0x38 */ s32 mItemFilterMode;
    u8 _3c[0xc0 - 0x3c];
};
static_assert(sizeof(RenderBufferContext) == 0xc0);

}  // namespace gsys
