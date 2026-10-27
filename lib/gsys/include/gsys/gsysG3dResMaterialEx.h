#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <gfx/seadGraphicsContext.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace nn::g3d {
class ResMaterial;
}

namespace gsys {

class ModelRenderCache;

namespace ModelEnum {
enum class ShaderAssignType;
}

// G3dResModelEx +0x18 is an array with stride 0x440 (ksys::tera 0x71011413b4); the destructor
// 0x7100c6d0fc is in a vtable and stores the vtable at +0.
class G3dResMaterialEx : public sead::hostio::Node {
public:
    virtual ~G3dResMaterialEx();

    // 0x7100c6d228: the record size, 0x440.
    static s32 calcRequiredMemorySize(const nn::g3d::ResMaterial* res_material);

    // 0x7100c6d21c: stores the material and its owner.
    void setResMaterial(nn::g3d::ResMaterial* res_material);

    // ModelResource::searchModelShader 0x7100c0c20c passes this to the shader archives.
    const nn::g3d::ResMaterial* getResMaterial() const { return mResMaterial; }

    // The 0xb8-byte shading-model record selected by the mask at +0xd8; internals unrecovered.
    struct ShadingModelInfo {
        u8 _0[0xb8];
    };
    // 0x7100c6d958
    const ShadingModelInfo* getShadingModelObj(ModelEnum::ShaderAssignType assign_type) const;
    // 0x7100c6d9cc (declared only)
    const char* getShaderOption(const sead::SafeString& name) const;
    // 0x7100c6d974
    bool isShaderOptionBool(const sead::SafeString& name) const;

    // Inline-only in the original; name is a guess.
    s16 getXluAlphaParamIndex() const { return mXluAlphaParamIndex; }

    // Tail of the record used by ModelRenderCache::loadResource 0x7100c809ac. The cache stores
    // the address of this sub-object at +0x298 to detect a material change, then copies the blend
    // and depth state from it. The types and names of the leading bytes are unrecovered.
    friend class ModelNW;
    friend class ModelRenderCache;

    struct RenderState {
        u8 _0[0x9];
        /* 0x2a1 */ u8 mType;
        u8 _a[0x10 - 0xa];
        /// Defaults of render view options 0 and 1. ModelNW::isDefaultRenderViewOptionEnabled
        /// 0x7100c066ec tests one bit of it.
        /* 0x2a8 */ u32 mRenderOptionFlags;
        /* 0x2ac */ bool mDepthTestEnable;
        /* 0x2ad */ u8 mDepthWriteEnable;
        u8 _ae[2];
        /* 0x2b0 */ u32 mBlendTargetCount;
        /* 0x2b4 */ sead::Color4f mBlendColor;
        u8 _2c4[0x2d4 - 0x2c4];
        /* 0x2d4 */ sead::GraphicsContext::BlendControl mBlendControl[8];
        u8 _304[0x310 - 0x304];
        /* 0x310 */ u8 mDepthFunc;
        u8 _311[0x440 - 0x298 - 0x79];
    };
    static_assert(offsetof(RenderState, mType) == 0x9);
    static_assert(offsetof(RenderState, mDepthTestEnable) == 0x14);
    static_assert(offsetof(RenderState, mBlendTargetCount) == 0x18);
    static_assert(offsetof(RenderState, mBlendColor) == 0x1c);
    static_assert(offsetof(RenderState, mBlendControl) == 0x3c);
    static_assert(offsetof(RenderState, mDepthFunc) == 0x78);

private:
    u8 _8[0xe - 0x8];
    /// Index into the resource's shader parameter array for the xlu alpha parameter, or -1.
    /// ModelNW::getMaterialParamXluAlpha 0x7100c04fdc loads it from +0xe.
    s16 mXluAlphaParamIndex;
    const nn::g3d::ResMaterial* mResMaterial;
    u8 _18[0x20 - 0x18];
    ShadingModelInfo mShadingModel;
    /* 0xd8 */ u32 mMask;
    u8 _dc[0x298 - 0xdc];
    /* 0x298 */ RenderState mRenderState;
};
static_assert(sizeof(G3dResMaterialEx) == 0x440);

}  // namespace gsys
