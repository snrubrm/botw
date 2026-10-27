#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
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
    struct Context {
        Context();
        ~Context();
        u32 _0;
        // Pass flags of the view's draw record: drawModelSceneCalcRenderView writes bits 7 / 8 / 11,
        // 12 (the record's analyze flag) and 19 (Graphics' _284 bit 0).
        /* 0x4 */ u32 mPassFlagsMaybe;
        u8 _8[0x3208 - 0x8];
        // Per-axis render scale. The Context constructor path 0x7100c5934c copies the two words
        // of the global pair at 0x7101e9ff10 into both this pair and 0x4b0/0x4b4; update
        // 0x7100c59684 loads them as f32, multiplies them by the viewport scale, and Graphics
        // calcModelSceneFrame 0x7100f30178 stores one f32 into both. DofMgr 0x71010d19b4 reads
        // +0x3208 as f32.
        f32 _3208;
        f32 _320c;
        // C5934C constructs a GBuffer and retains it here; C590D4 destroys it.
        GBuffer* mGBuffer;
        u8 _3218[0x3878 - 0x3218];
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
