#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <gfx/seadColor.h>
#include <prim/seadBitFlag.h>

namespace agl {
class DrawContext;
class UniformBlock;
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

    // Inline-only accessor names follow the fields read by Graphics F34F1C and
    // ModelScene::drawProcedural C13EA0.
    agl::DrawContext* getDrawContext() const { return mDrawContext; }
    u32 getViewIndex() const { return mViewIndex; }

private:
    u8 _0[0x10];
    const ModelRenderContext* mContext;
    agl::DrawContext* mDrawContext;
    u8 mViewIndex;
    u8 mShaderAssignType;
    u8 _22;
    u8 _23;
    u8 _24[4];
    agl::UniformBlock* mRenderUBO;
    u8 _30[5];
    u8 mBlendMask;
    u16 _36;
    u8 _38;
    u8 mPassViewProjIndex;
    u8 _3a[2];
    u32 mChannelMask;
    u8 _40[0x148 - 0x40];
    s32 _148;
    u8 _14c[0x18c - 0x14c];
    sead::Color4f mForceBlendColor;
    u8 _19c[0x250 - 0x19c];
    ModelRenderStatistics* mStatistics;
};
static_assert(sizeof(ModelRenderCache) == 0x258);

}  // namespace gsys
