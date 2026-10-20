#pragma once

#include <container/seadBuffer.h>
#include <cull/aglViewFrustumCulling.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

namespace agl {
class DrawContext;
class RenderBuffer;
class TextureData;
}
namespace sead {
class DrawContext;
class Viewport;
class Projection;
}

namespace gsys {

class ShaderContext;
class ModelRenderQueue;

namespace ModelEnum {
// 0x7100c08334 indexes the eight float pairs at +0x2d0 with this type.
enum class PolygonOffsetType;
enum class ShaderAssignType;
}

// Two independent allocations (0x7100c2e1e0 and 0x7100f273ac) reserve 0x388
// bytes, call constructor 0x7100c07fb0, then the named initialize method.
class ModelRenderContext {
    friend class ModelRenderCache;
public:
    struct CreateArg {
        CreateArg();
        int _0;
        int viewCount;
    };

    // Both native constructors (0x7100c07f18 / 0x7100c07f60) copy a SafeString,
    // retain the queue, and initialize this 0x48-byte draw request. draw consumes
    // every field below; the unnamed options keep their offset names.
    struct DrawArg {
        DrawArg(const sead::SafeString& name, const ModelRenderQueue& queue,
                const sead::BitFlag32& mask, u32 value, ModelEnum::ShaderAssignType type,
                int view, u32 options, u32 material);
        DrawArg(const sead::SafeString& name, const ModelRenderQueue& queue,
                const sead::BitFlag32& mask, ModelEnum::ShaderAssignType type, int view,
                u32 options, u32 material);

        sead::SafeString mName;
        const ModelRenderQueue& mQueue;
        sead::BitFlag32 mMask;
        u32 _1c;
        ModelEnum::ShaderAssignType mShaderAssignType;
        int mViewIndex;
        u32 mOptions;
        u32 mMaterialIndex;
        u32 _30 = 0xf;
        u32 _34 = 1;
        u32 _38 = 0;
        s32 _3c = -1;
        s32 _40 = -1;
        u32 _44 = 0;
    };
    static_assert(sizeof(DrawArg) == 0x48);

    ModelRenderContext();
    virtual ~ModelRenderContext();

    void initialize(const CreateArg&, sead::Heap*);
    void calcGPU(bool flag) const;
    // 0x7100c08344 / 0x7100c08564: original names and signatures in the CSV.
    void calcView(int view, const sead::Matrix34f&, const sead::Projection&,
                  const sead::Matrix34f&);
    void draw(agl::DrawContext*, const DrawArg&) const;
    // 0x7100c0887c (name is a guess): binds the render buffer, then applies the viewport to it.
    void bind(sead::DrawContext* draw_context) const;
    // 0x7100c08334: stores the two values in the pair selected by `type`.
    void setPolygonOffset(ModelEnum::PolygonOffsetType type, f32 a, f32 b);

    // Native 0x7100c082fc/0x7100c08310 index the two 43-entry pointer arrays
    // at +0x20/+0x178 with the sign-extended type. The original enumerator
    // spellings are unrecovered; only the type values used by callers (4, 5,
    // 7, 0x15, 0x16, ...) are proved.
    enum PassTextureType : int {
        PassTextureType_Count = 43,
    };
    void pushPassTexture(PassTextureType type, const agl::TextureData* texture);
    void popPassTexture(PassTextureType type);

private:
    // initialize allocates this buffer with 0x3a0-byte entries and constructs
    // each frustum at +0x60. reset 0x7100c08098 initializes both leading matrices.
    struct ViewData {
        sead::Matrix34f view;
        sead::Matrix34f inverseView;
        agl::cull::ViewFrustumCulling frustum;
        u8 _298[0x390 - 0x298];
        // initialize 0x7100c0820c clears this byte after constructing each frustum.
        u8 _390 = 0;
        u8 _391[0x3a0 - 0x391];
    };
    static_assert(sizeof(ViewData) == 0x3a0);

    u8 _8[8];
    sead::Buffer<ViewData> mViewData;  // +0x10
    const agl::TextureData* mPassTextures[43];       // +0x20
    const agl::TextureData* mSavedPassTextures[43];  // +0x178
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
