#pragma once

#include <basis/seadTypes.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureEnum.h>
#include <common/aglTextureSampler.h>
#include <common/aglUniformBlock.h>
#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>

namespace agl {
class DrawContext;
class RenderTargetColor;
namespace lght {
class LightPrePass;
}
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
    // invalidatePreShading 0x7100c737a8 indexes its records with this type; the callers pass
    // 0 and 2..5 and the enumerator spellings are unrecovered.
    enum class PreShadingBufferType : int;

    GBuffer();
    virtual ~GBuffer();
    void initialize(sead::Heap* heap);
    // 0x7100c73834 (declared only)
    void invalidate();
    // 0x7100c73a80: frees one resolution's buffer-type texture and clears its flag.
    void invalidate(Resolution resolution, BufferType type);
    // 0x7100c72f18 / 0x7100c7303c / 0x7100c73b40 (declared only)
    void endPreShading(agl::DrawContext*);
    void expand(agl::DrawContext*);
    void entryToDebugTexturePage(agl::DrawContext*, int, const agl::utl::DebugTexturePage*);
    // 0x7100c73cf4: nothing in the retail build.
    void entryToDebugTexturePagePreShading(agl::DrawContext*, int,
                                           const agl::utl::DebugTexturePage*);
    void invalidateGPUWriteCache(agl::DrawContext*, const sead::SafeString&, Resolution) const;
    // 0x7100c72f94: invalidates the eight colour targets of the second resolution's render
    // buffer. The name argument is unused in the release build.
    void invalidateGPUWriteCachePreShading(agl::DrawContext*, const sead::SafeString&) const;

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
    /// Inline-only accessor: the first resolution's render buffer at +0x770.
    agl::RenderBuffer* getRenderBuffer() { return &mResolutionData[0].mRenderBuffer; }
    // 0x7100c737a8
    void invalidatePreShading(PreShadingBufferType type);
    // 0x7100c7367c / 0x7100c73734: the deferred-shading pass around the material-ID expansion.
    void beginDeferredShading(agl::DrawContext*, MaterialIdMask, agl::TextureCompSel);
    void endDeferredShading();
    // 0x7100c71e7c: binds one resolution's render buffer and applies its viewport.
    void bindRenderBuffer(agl::DrawContext*, Resolution) const;
    // 0x7100c7256c: swaps the two colour targets the resolution's records select.
    void swapRenderTarget();
    // 0x7100c73cf8: stores a colour target in a resolution's render buffer and ORs the mask
    // into the two accumulated words.
    void setRenderTargetColor(Resolution resolution, int index, agl::RenderTargetColor* target,
                              u32 mask);

    // begin 0x7100c715c4 accumulates 4-bit material IDs per pre-shading buffer into +0x1f84; the
    // grudge renderer 0x710128f798 copies that word and its sibling +0x1f88 into its draw arg
    // (DrawArg + 0x30 / +0x34). The sibling's name is a guess: only clearRenderingFlags
    // 0x7100c71284 writes it (to zero).
    u32 getMaterialIdMask() const { return _1f84; }
    u32 getBlendMaskMaybe() const { return _1f88; }
    // drawGBufferXluSeal 0x7100c184a8 and drawGBufferXluOpa 0x7100c187a4 read the two words
    // that follow; the names are guesses, only the order is known.
    u32 getMaterialIdMaskXluSealMaybe() const { return _1f8c; }
    u32 getBlendMaskXluSealMaybe() const { return _1f90; }

private:
    struct BufferRecord {
        agl::TextureFormat mFormat;
        u32 mReduceFilter;
        sead::Color4f mClearColor;
        // The constructor 0x7100c70958 builds a colour target at +0x18 of every record; the
        // destructor 0x7100c70da4 destroys them.
        agl::RenderTargetColor mColorTarget;  // 18
        // Constructor 0x7100c70958 stores -1 here; swapRenderTarget 0x7100c7256c swaps the two
        // targets selected by records 0 and 3.
        s8 _190;
        u8 _191;
        u8 mFlags;  // 192
        u8 _193[0x198 - 0x193];
    };
    static_assert(sizeof(BufferRecord) == 0x198);

    // The five texture/sampler pairs the constructor 0x7100c70ce4 builds in every resolution
    // block; invalidate 0x7100c73a80 frees one by type.
    struct ResolutionPreShadingBuffer {
        const agl::TextureData* mTexture;
        agl::TextureSampler mSampler;
    };
    static_assert(sizeof(ResolutionPreShadingBuffer) == 0x178);

    // Two 0x940-byte blocks at +0x10, each with its own render buffer at +0x760 and the
    // pre-shading flags at +0x758 (constructor 0x7100c70958 and isRendering 0x7100c7159c).
    struct ResolutionData {
        ResolutionPreShadingBuffer mPreShadingBuffers[5];  // 0
        u32 mFlags;                                      // 758
        agl::RenderBuffer mRenderBuffer;                  // 760
        agl::RenderTargetDepth mDepthTarget;              // 7c8
    };
    static_assert(sizeof(ResolutionData) == 0x940);

    u8 _8;
    // Pre-shading buffer flags: invalidatePreShading 0x7100c737a8 clears the bit of its type.
    u8 _9;
    u8 _a[0x10 - 0xa];
    ResolutionData mResolutionData[2];  // 10
    // The per-buffer-type records setFormat 0x7100c73af4 and its siblings index with the
    // `type * 0x198 + 0x1290` arithmetic. Only indices 0..4 are records; the original's record 5
    // is the 0x78 UniformBlock that follows, so the array stops here.
    BufferRecord mBufferRecords[5];
    // The address setFormat's `type * 0x198 + 0x1290` arithmetic reaches for type 5; the
    // constructor 0x7100c70958 builds a UniformBlock there.
    /* 0x1a88 */ agl::UniformBlock mUniformBlock;
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
    /* 0x1f90 */ u32 _1f90;
    u8 _1f94[0x1f98 - 0x1f94];
    // The second per-buffer record array; the constructor builds its six colour targets and
    // clear colours the same way as mBufferRecords.
    BufferRecord mBufferRecordsPreShading[6];  // 1f98
    // The pre-shading buffers constructor 0x7100c70958 builds at 0x2928-step strides: each holds
    // the dynamic texture invalidatePreShading 0x7100c737a8 frees and its sampler. The sampler at
    // 0x31f8 after the records and the light pre-pass pair at 0x3368 are modelled too.
    struct PreShadingBuffer {
        const agl::TextureData* mTexture;
        agl::TextureSampler mSampler;
    };
    static_assert(sizeof(PreShadingBuffer) == 0x178);
    PreShadingBuffer mPreShadingBuffers[6];  // 2928
    agl::TextureSampler _31f8;               // 31f8
    agl::lght::LightPrePass* mLightPrePass;  // 3368
    s8 mLightPrePassView;                    // 3370
    u8 _3371[0x3378 - 0x3371];
};
static_assert(sizeof(GBuffer) == 0x3378);

}  // namespace gsys
