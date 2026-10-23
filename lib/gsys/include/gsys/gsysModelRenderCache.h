#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <gfx/seadColor.h>
#include <gfx/seadGraphicsContext.h>
#include <prim/seadBitFlag.h>

namespace agl {
class DrawContext;
class UniformBlock;
}
namespace agl::cull {
class OcclusionQuery;
}

namespace gsys {
class ModelRenderContext;
class ModelRenderStatistics;
namespace ModelEnum {
enum class ShaderAssignType;
}

// Constructor C80100 initializes through the statistics pointer at +0x250.
// ModelRenderContext::draw C08564 constructs this object in a 0x258-byte stack range.
class ModelRenderCache {
public:
    ModelRenderCache(agl::DrawContext*, const ModelRenderContext*, sead::BitFlag32, u32,
                     ModelEnum::ShaderAssignType, u32, u32, u32, u32, ModelRenderStatistics*);
    ~ModelRenderCache();

    void setBlendMask(u32 mask);
    void setChannelMask(u32 mask);
    void setPassViewProjIndex(int index);
    void setForceBlendColor(const sead::Color4f& color);
    // 0x7100c80574: returns the cache to its default render state.
    void reset();

    // Inline-only accessor names follow the fields read by Graphics F34F1C and
    // ModelScene::drawProcedural C13EA0.
    agl::DrawContext* getDrawContext() const { return mDrawContext; }
    u32 getViewIndex() const { return mViewIndex; }

private:
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _c;
    const ModelRenderContext* mContext;
    agl::DrawContext* mDrawContext;
    u8 mViewIndex;
    u8 mShaderAssignType;
    u8 _22;
    u8 _23;
    u8 _24[4];
    agl::UniformBlock* mRenderUBO;
    u8 _30;
    u8 _31;
    u8 _32;
    u8 _33;
    u8 _34;
    u8 mBlendMask;
    u16 _36;
    u8 _38;
    u8 mPassViewProjIndex;
    u8 _3a[2];
    u32 mChannelMask;
    u32 _40;
    u8 _44[0x148 - 0x44];
    /// The pass view-projection indices; -1 when a slot is unused.
    s32 _148[16];
    u8 _188[0x18c - 0x188];
    sead::Color4f mForceBlendColor;
    u8 _19c[0x1a0 - 0x19c];
    agl::cull::OcclusionQuery* mOcclusionQuery;
    u64 _1a8;
    u64 _1b0;
    u64 _1b8;
    u64 _1c0;
    sead::GraphicsContext mGraphicsContext;
    u8 _23c[0x240 - 0x23c];
    u64 _240;
    u32 _248;
    u32 _24c;
    ModelRenderStatistics* mStatistics;
};
static_assert(sizeof(ModelRenderCache) == 0x258);

}  // namespace gsys
