#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <common/aglShaderLocation.h>
#include <gfx/seadColor.h>
#include <gfx/seadGraphicsContext.h>
#include <prim/seadBitFlag.h>
#include "gsys/gsysG3dResMaterialEx.h"

namespace agl {
class DrawContext;
class TextureSampler;
class UniformBlock;
}
namespace agl::cull {
class OcclusionQuery;
}

namespace gsys {
class ModelRenderContext;
class ModelRenderStatistics;
class G3dResShaderProgramEx;
class G3dResShapeEx;
class ModelRenderUnitNW;
class ModelAssignRenderInfo;
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
    // 0x7100c80438
    void loadOcclusionQuery(const agl::cull::OcclusionQuery* query);
    // 0x7100c809ac: binds the unit's shape, material and shader state.
    bool loadResource(const ModelRenderUnitNW* unit);
    // 0x7100c80ff4
    void loadResShaderProgram_(const ModelRenderUnitNW& unit, const ModelAssignRenderInfo& info);
    // 0x7100c80694: the cull-face and polygon-mode mapping reset also uses. Static; the native
    // first argument is the GraphicsContext.
    static void setGraphicsContextToPolygonCtrl(sead::GraphicsContext* context, u32 flags);
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
    s8 _38;
    u8 mPassViewProjIndex;
    u8 _3a[2];
    u32 mChannelMask;
    u32 _40;
    /// The texture samplers copied from the render context by the constructor.
    const agl::TextureSampler* mTextureSamplers[29];
    u8 _130[0x148 - 0x130];
    /// The current shader program id.
    s32 _148;
    /// Cached shader program locations; the constructor and reset invalidate them.
    agl::ShaderLocation _14c[16] = {
        agl::ShaderLocation(-1), agl::ShaderLocation(-1), agl::ShaderLocation(-1),
        agl::ShaderLocation(-1), agl::ShaderLocation(-1), agl::ShaderLocation(-1),
        agl::ShaderLocation(-1), agl::ShaderLocation(-1), agl::ShaderLocation(-1),
        agl::ShaderLocation(-1), agl::ShaderLocation(-1), agl::ShaderLocation(-1),
        agl::ShaderLocation(-1), agl::ShaderLocation(-1), agl::ShaderLocation(-1),
        agl::ShaderLocation(-1)};
    sead::Color4f mForceBlendColor;
    u8 _19c[0x1a0 - 0x19c];
    const agl::cull::OcclusionQuery* mOcclusionQuery;
    const G3dResShapeEx* _1a8;
    G3dResShaderProgramEx* mShaderProgram;
    const G3dResMaterialEx::RenderState* _1b8;
    u64 _1c0;
    sead::GraphicsContext mGraphicsContext;
    u8 _23c[0x240 - 0x23c];
    u64 _240;
    u32 _248;
    u32 _24c;
    ModelRenderStatistics* mStatistics;
};
static_assert(sizeof(ModelRenderCache) == 0x258);

// Partial: the constructor 0x7100c81184 stores a vtable at +0 (the destructor is the only
// virtual), zeroes the words at +8..+0x14 and constructs the sead::GraphicsContext at +0x14;
// update 0x7100c811c0 is still undecompiled.
class ModelRenderState {
public:
    ModelRenderState();
    virtual ~ModelRenderState();

private:
    u16 _8 = 0;
    u8 _a = 1;
    u8 _b = 0;
    u16 _c = 0;
    u32 _10 = 0;
    sead::GraphicsContext mGraphicsContext;  // 0x14
};

}  // namespace gsys
