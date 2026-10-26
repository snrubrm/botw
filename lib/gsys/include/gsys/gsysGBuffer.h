#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureEnum.h>
#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>

namespace agl {
class DrawContext;
class RenderTargetColor;
namespace utl {
class DebugTexturePage;
}
}

namespace gsys {

// RenderBufferContext::initialize C5934C allocates 0x3378 bytes and calls C70958.
// The constructor installs the destructor-only vtable 24D0DA8; remaining state is opaque.
class GBuffer {
public:
    enum class Resolution : int;
    enum class BufferType : int;
    enum class MaterialIdMask : int;

    GBuffer();
    virtual ~GBuffer();
    void initialize(sead::Heap* heap);
    // 0x7100c73834 (declared only)
    void invalidate();
    // 0x7100c72f18 / 0x7100c7303c / 0x7100c73b40 (declared only)
    void endPreShading(agl::DrawContext*);
    void expand(agl::DrawContext*);
    void entryToDebugTexturePage(agl::DrawContext*, int, const agl::utl::DebugTexturePage*);
    // 0x7100c73cf4: nothing in the retail build.
    void entryToDebugTexturePagePreShading(agl::DrawContext*, int,
                                           const agl::utl::DebugTexturePage*);
    void invalidateGPUWriteCache(agl::DrawContext*, const sead::SafeString&, Resolution) const;

    // 0x7100c73af4: per-buffer format.
    void setFormat(BufferType type, agl::TextureFormat format);
    // 0x7100c73b30: per-buffer reduce filter.
    void setReduceFilter(BufferType type, agl::TextureFilterType filter);
    // 0x7100c73b04: sets or clears bit 1 of the per-buffer flags.
    void enableMEM2(BufferType type, bool enable);
    // 0x7100c7259c: sets or clears bit 0 of the per-buffer flags and stores the clear colour.
    void setClearColor(BufferType type, bool enable, const sead::Color4f& color);
    // 0x7100c7158c: per-material-id byte at +0x1f80.
    void setMaterialIdMask(MaterialIdMask mask, u8 value);
    // 0x7100c72f08: forwards the Xlu pre-shading step.
    void forwardPreShadingStepForXlu(agl::DrawContext* draw_context, int);
    // 0x7100c720c0 (declared only)
    void expandMaterialID_(agl::DrawContext*, Resolution, MaterialIdMask, agl::TextureCompSel);

    // 0x7100c7159c: whether either resolution's pre-shading buffers are flagged.
    bool isRendering() const;
    // 0x7100c7367c / 0x7100c73734: the deferred-shading pass around the material-ID expansion.
    void beginDeferredShading(agl::DrawContext*, MaterialIdMask, agl::TextureCompSel);
    void endDeferredShading();

    // begin 0x7100c715c4 accumulates 4-bit material IDs per pre-shading buffer into +0x1f84; the
    // grudge renderer 0x710128f798 copies that word and its sibling +0x1f88 into its draw arg
    // (DrawArg + 0x30 / +0x34). The sibling's name is a guess: only clearRenderingFlags
    // 0x7100c71284 writes it (to zero).
    u32 getMaterialIdMask() const { return _1f84; }
    u32 getBlendMaskMaybe() const { return _1f88; }

private:
    struct BufferRecord {
        agl::TextureFormat mFormat;
        u32 mReduceFilter;
        sead::Color4f mClearColor;
        u8 _18[0x192 - 0x18];
        u8 mFlags;
        u8 _193[0x198 - 0x193];
    };
    static_assert(sizeof(BufferRecord) == 0x198);

    u8 _8[0x768 - 8];
    // Bit 2 selects the material-ID expansion path of beginDeferredShading 0x7100c7367c. Bits 0..4
    // are the pre-shading buffer flags isRendering tests.
    u8 mFlags768;
    u8 _769[0x770 - 0x769];
    // 0x7100c7367c stores RenderTargetColor 0x1b00 into this render buffer's first colour slot.
    /* 0x0770 */ agl::RenderBuffer mRenderBuffer;
    u8 _7d8[0x10a8 - 0x7d8];
    // The same pre-shading buffer flags one 0x940-byte resolution block later (bindRenderBuffer
    // indexes the block at 0x940 steps).
    u8 mFlags10a8;
    u8 _10a9[0x1290 - 0x10a9];
    // The per-buffer-type records setFormat 0x7100c73af4 and its siblings index with the
    // `type * 0x198 + 0x1290` arithmetic. Only indices 0..4 are records; the original's record 5
    // is the 0x78 UniformBlock that follows, so the array stops here.
    BufferRecord mBufferRecords[5];
    u8 _1a88[0x1b00 - 0x1a88];
    // The three targets the constructor 0x7100c70958 creates before the second record array.
    // The deferred-shading pass binds 0x1b00 as colour 0 and clears the depth target's storage.
    /* 0x1b00 */ agl::RenderTargetColor mDeferredColorTarget;
    /* 0x1c78 */ agl::RenderTargetColor mDeferredColorTarget2;
    /* 0x1df0 */ agl::RenderTargetDepth mDeferredDepthTarget;
    // The expansion texture expandMaterialID_ 0x7100c720c0 allocates and endDeferredShading frees.
    /* 0x1f68 */ agl::TextureData* mExpandMaterialIdTexture;
    u8 _1f70[0x1f80 - 0x1f70];
    // The byte array setMaterialIdMask 0x7100c7158c writes; the next member starts at +0x1f84.
    u8 mMaterialIdMasks[4];
    /* 0x1f84 */ u32 _1f84;
    /* 0x1f88 */ u32 _1f88;
    /* 0x1f8c */ u32 _1f8c;
    u8 _1f90[0x3378 - 0x1f90];
};
static_assert(sizeof(GBuffer) == 0x3378);

}  // namespace gsys
