#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>

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
        u8 _0[0x3208];
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

private:
    sead::Buffer<Context> mContexts;
    u8 _18[0xc0 - 0x18];
};
static_assert(sizeof(RenderBufferContext) == 0xc0);

}  // namespace gsys
