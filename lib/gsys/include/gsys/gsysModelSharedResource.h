#pragma once

#include <basis/seadTypes.h>
#include <common/aglUniformBlock.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace gsys {

namespace ModelEnum {
// The name getters index their string tables with a zero-extended value, so these are plain
// (unsigned) enums. Enumerator names follow the table strings.
enum LightMapType {
    cLightMapType_Diffuse,
    cLightMapType_Specular,
};
enum RenderInfoBool {
    cRenderInfoBool_DynamicDepthShadow,
    cRenderInfoBool_DynamicDepthShadowOnly,
    cRenderInfoBool_StaticDepthShadow,
    cRenderInfoBool_StaticDepthShadowOnly,
    cRenderInfoBool_CubeMap,
    cRenderInfoBool_CubeMapOnly,
    cRenderInfoBool_Bake,
    cRenderInfoBool_DynamicProjection,
    cRenderInfoBool_DynamicReflection,
};
enum RenderInfoState {
    cRenderInfoState_RenderStateMode,
    cRenderInfoState_RenderStateDisplayFace,
    cRenderInfoState_RenderStateBlendMode,
    cRenderInfoState_DepthTestEnable,
    cRenderInfoState_DepthTestWrite,
    cRenderInfoState_DepthTestFunc,
    cRenderInfoState_AlphaTestEnable,
    cRenderInfoState_AlphaTestFunc,
    cRenderInfoState_AlphaTestValue,
    cRenderInfoState_ColorBlendRgbSrcFunc,
    cRenderInfoState_ColorBlendRgbDstFunc,
    cRenderInfoState_ColorBlendRgbOp,
    cRenderInfoState_ColorBlendAlphaSrcFunc,
    cRenderInfoState_ColorBlendAlphaDstFunc,
    cRenderInfoState_ColorBlendAlphaOp,
    cRenderInfoState_ColorBlendConstColor,
};
enum RenderStateMode {
    cRenderStateMode_Opaque,
    cRenderStateMode_Mask,
    cRenderStateMode_Translucent,
    cRenderStateMode_Custom,
};
enum DisplayFaceType {
    cDisplayFaceType_Both,
    cDisplayFaceType_Front,
    cDisplayFaceType_Back,
    cDisplayFaceType_None,
};
enum BlendMode {
    cBlendMode_None,
    cBlendMode_Color,
    cBlendMode_Logic,
};
enum PassType {
    cPassType_NoSetting,
    cPassType_Seal,
    cPassType_XluWater,
    cPassType_ReducedBuffer,
};
enum class PriorityHintType : int;
}  // namespace ModelEnum

// Shared render-info names and uniform blocks. createInstance 0x7100c6a95c allocates 0x288
// bytes; the disposer destroys the instance through vtable slot 0, the destructor.
class ModelSharedResource {
    SEAD_SINGLETON_DISPOSER(ModelSharedResource)
public:
    // 0x7100c6a95c (createInstance) is U: the inlined constructor also fills a static 3x4
    // matrix whose source form is not recovered, so the constructor is declared only.
    ModelSharedResource();
    virtual ~ModelSharedResource();

    // 0x7100c6aaf8 (declared only).
    void initialize(sead::Heap* heap);

    static sead::SafeString getRenderInfoEnvObjSetName();
    static sead::SafeString getRenderInfoLightName(ModelEnum::LightMapType type);
    static sead::SafeString getRenderInfoPassName();
    static sead::SafeString getRenderInfoBoolName(ModelEnum::RenderInfoBool type);
    static sead::SafeString getRenderInfoStateName(ModelEnum::RenderInfoState type);
    static sead::SafeString getRenderStateModeName(ModelEnum::RenderStateMode mode);
    static sead::SafeString getDisplayFaceTypeName(ModelEnum::DisplayFaceType type);
    static sead::SafeString getBlendModeName(ModelEnum::BlendMode mode);
    static sead::SafeString getRenderInfoPriorityHintName();
    static ModelEnum::PriorityHintType getPriorityHintType(const sead::SafeString& name);
    static sead::SafeString getRenderInfoPriorityName();
    static bool isRenderInfoBoolEnabled(const sead::SafeString& value);
    static sead::SafeString getPassTypeName(ModelEnum::PassType type);

private:
    agl::UniformBlock _28;
    agl::UniformBlock _a0;
    agl::UniformBlock _118;
    agl::UniformBlock _190;
    agl::UniformBlock _208;
    u8 _280[0x288 - 0x280];
};

}  // namespace gsys
