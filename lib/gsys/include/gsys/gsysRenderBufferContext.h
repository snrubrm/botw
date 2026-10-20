#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>

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
        u8 _0[0x3210];
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

private:
    sead::Buffer<Context> mContexts;
    u8 _18[0xc0 - 0x18];
};
static_assert(sizeof(RenderBufferContext) == 0xc0);

}  // namespace gsys
