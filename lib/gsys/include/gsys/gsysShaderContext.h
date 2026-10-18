#pragma once

#include <cstddef>
#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace agl {
class RenderBuffer;
}
namespace sead {
class Viewport;
}

namespace agl::cull {
class ViewFrustumCulling;
}

namespace gsys {

class ModelNW;

// ModelRenderContext::initialize 0x7100c0820c allocates 0x58 bytes and calls
// constructor 0x7100c5d7b8. The buffer element lifetimes are visible in
// 0x7100c5d7d4; that row's existing PrimitiveOcclusionHolder identity is unresolved.
class ShaderContext {
public:
    ShaderContext();
    ~ShaderContext();

    void initialize(int, int, sead::Heap*);
    void setEnvStruct(int index, void* ptr, u64 size);
    void setAreaOverride(int index, f32 value, int first, int second);
    // Name inferred from ModelSceneGI::setSceneMaterial (0x7100c309d0), which
    // forwards the same ModelNW pointer to this method at 0x7100c5dd30.
    void setSceneMaterial(ModelNW* model);
    agl::UniformBlock* getContextRenderUBO(int index) const;
    void calcGpuViewFlush(int index, const sead::Matrix34f& view,
                          const sead::Matrix44f& projection,
                          const agl::cull::ViewFrustumCulling& frustum, bool, bool);
    void calcGpuRenderBuffer(const agl::RenderBuffer& buffer, const sead::Viewport& viewport);
    void calcGpuDepthShadow(f32 a, f32 b, f32 c, f32 d, const sead::Vector2f& offset);
    void calcGpuDepthShadowCascade(int index, const sead::Matrix44f& matrix);

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
        // setAreaOverride 0x7100c5df0c stores the two integers and float here.
        u16 _78;
        u16 _7a;
        f32 _7c;
        // setEnvStruct 0x7100c5dd38 retains the pointer and low 32 bits of size.
        void* mEnvStruct;
        u32 mEnvStructSize;
        u8 _8c[0xb8 - 0x8c];
    };
    static_assert(sizeof(RenderUBO) == 0xb8);
    static_assert(offsetof(RenderUBO, _78) == 0x78);
    static_assert(offsetof(RenderUBO, _7a) == 0x7a);
    static_assert(offsetof(RenderUBO, _7c) == 0x7c);
    static_assert(offsetof(RenderUBO, mEnvStruct) == 0x80);
    static_assert(offsetof(RenderUBO, mEnvStructSize) == 0x88);

    sead::Buffer<ViewUBO> mViewUBOs;
    u8 _10[0x38 - 0x10];
    sead::Buffer<RenderUBO> mRenderUBOs;
    u8 _48;
    u8 _49[7];
    // Scene initialization and ModelSceneGI::setSceneMaterial supply ModelNW*.
    ModelNW* mSceneMaterial;
};
static_assert(sizeof(ShaderContext) == 0x58);

}  // namespace gsys
