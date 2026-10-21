#pragma once

#include <basis/seadTypes.h>
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
    // 0x7100c73cf4: nothing in the retail build.
    void entryToDebugTexturePagePreShading(agl::DrawContext*, int,
                                           const agl::utl::DebugTexturePage*);
    void invalidateGPUWriteCache(agl::DrawContext*, const sead::SafeString&, Resolution) const;

    // 0x7100c73af4: per-buffer format. setReduceFilter 0x7100c73b30 stays U because
    // agl::TextureFilterType is not in the agl headers.
    void setFormat(BufferType type, agl::TextureFormat format);
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

    u8 _8[0x1290 - 8];
    // Eight 0x198-byte records; the next array starts at +0x1f80.
    BufferRecord mBufferRecords[8];
    u8 _1f50[0x1f80 - 0x1f50];
    // The byte array setMaterialIdMask 0x7100c7158c writes; the next member starts at +0x1f84.
    u8 mMaterialIdMasks[4];
    /* 0x1f84 */ u32 _1f84;
    /* 0x1f88 */ u32 _1f88;
    /* 0x1f8c */ u32 _1f8c;
    u8 _1f90[0x3378 - 0x1f90];
};
static_assert(sizeof(GBuffer) == 0x3378);

}  // namespace gsys
