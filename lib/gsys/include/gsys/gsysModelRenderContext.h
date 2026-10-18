#pragma once

#include <container/seadBuffer.h>
#include <cull/aglViewFrustumCulling.h>
#include <math/seadMatrix.h>

namespace agl {
class RenderBuffer;
}
namespace sead {
class Viewport;
}

namespace gsys {

class ShaderContext;

// Two independent allocations (0x7100c2e1e0 and 0x7100f273ac) reserve 0x388
// bytes, call constructor 0x7100c07fb0, then the named initialize method.
class ModelRenderContext {
public:
    struct CreateArg {
        CreateArg();
        int _0;
        int viewCount;
    };

    ModelRenderContext();
    virtual ~ModelRenderContext();

    void initialize(const CreateArg&, sead::Heap*);
    void calcGPU(bool flag) const;

private:
    // initialize allocates this buffer with 0x3a0-byte entries and constructs
    // each frustum at +0x60. reset 0x7100c08098 initializes both leading matrices.
    struct ViewData {
        sead::Matrix34f view;
        sead::Matrix34f inverseView;
        agl::cull::ViewFrustumCulling frustum;
        u8 _298[0x390 - 0x298];
        // initialize 0x7100c0820c clears this byte after constructing each frustum.
        bool _390 = false;
        u8 _391[0x3a0 - 0x391];
    };
    static_assert(sizeof(ViewData) == 0x3a0);

    u8 _8[8];
    sead::Buffer<ViewData> mViewData;  // +0x10
    u8 _20[0x2d0 - 0x20];
    // initialize clears eight pairs. 0x7100c08334 sets two floats at the indexed
    // pair's +0/+4; their meanings are not known.
    struct FloatPair {
        f32 _0;
        f32 _4;
    };
    static_assert(sizeof(FloatPair) == 8);
    FloatPair mUnk2d0[8];
    ShaderContext* mShaderContext;  // +0x310, owned by initialize/destructor
    u8 _318[8];
    const agl::RenderBuffer* mRenderBuffer;
    const sead::Viewport* mViewport;
    // Includes the contained callback object at +0x368. Its signature and
    // lifetime remain unknown; constructor/destructor bodies stay undecompiled.
    u8 _330[0x388 - 0x330];
};
static_assert(sizeof(ModelRenderContext) == 0x388);

}  // namespace gsys
