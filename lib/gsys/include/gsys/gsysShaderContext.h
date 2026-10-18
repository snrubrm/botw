#pragma once

#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>

namespace agl::cull {
class ViewFrustumCulling;
}

namespace gsys {

// ModelRenderContext::initialize 0x7100c0820c allocates 0x58 bytes and calls
// constructor 0x7100c5d7b8. The buffer element lifetimes are visible in
// 0x7100c5d7d4; that row's existing PrimitiveOcclusionHolder identity is unresolved.
class ShaderContext {
public:
    ShaderContext();
    ~ShaderContext();

    void initialize(int, int, sead::Heap*);
    agl::UniformBlock* getContextRenderUBO(int index) const;
    void calcGpuViewFlush(int index, const sead::Matrix34f& view,
                          const sead::Matrix44f& projection,
                          const agl::cull::ViewFrustumCulling& frustum, bool, bool);

private:
    // initialize 0x7100c5d874 constructs a UniformBlock at +8 of each 0x80-byte
    // entry. getContextRenderUBO 0x7100c5dcf0 sets bit0 before returning that block.
    struct ViewUBO {
        u8 flags;
        u8 _1[7];
        agl::UniformBlock block;
    };
    static_assert(sizeof(ViewUBO) == 0x80);

    // The other buffer has 0xb8-byte entries, each beginning with a UniformBlock.
    // Its remaining state is not modelled; no lifetime bodies are defined here.
    struct RenderUBO {
        agl::UniformBlock block;
        u8 _78[0xb8 - 0x78];
    };
    static_assert(sizeof(RenderUBO) == 0xb8);

    sead::Buffer<ViewUBO> mViewUBOs;
    u8 _10[0x38 - 0x10];
    sead::Buffer<RenderUBO> mRenderUBOs;
    bool _48;
    u8 _49[0x58 - 0x49];
};
static_assert(sizeof(ShaderContext) == 0x58);

}  // namespace gsys
