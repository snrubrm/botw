#include "gsys/gsysModelSharedResource.h"

namespace gsys {

namespace {

// 0x71024d0680
const char* const sLightMapTypeNames[] = {"gsys_light_diffuse", "gsys_light_specular"};

// 0x71024d0690
const char* const sRenderInfoBoolNames[] = {
    "gsys_dynamic_depth_shadow", "gsys_dynamic_depth_shadow_only", "gsys_static_depth_shadow",
    "gsys_static_depth_shadow_only", "gsys_cube_map", "gsys_cube_map_only",
    "gsys_bake", "gsys_dynamic_projection", "gsys_dynamic_reflection",
};

// 0x71024d06d8
const char* const sRenderInfoStateNames[] = {
    "gsys_render_state_mode",
    "gsys_render_state_display_face",
    "gsys_render_state_blend_mode",
    "gsys_depth_test_enable",
    "gsys_depth_test_write",
    "gsys_depth_test_func",
    "gsys_alpha_test_enable",
    "gsys_alpha_test_func",
    "gsys_alpha_test_value",
    "gsys_color_blend_rgb_src_func",
    "gsys_color_blend_rgb_dst_func",
    "gsys_color_blend_rgb_op",
    "gsys_color_blend_alpha_src_func",
    "gsys_color_blend_alpha_dst_func",
    "gsys_color_blend_alpha_op",
    "gsys_color_blend_const_color",
};

// 0x71024d0758
const char* const sRenderStateModeNames[] = {"opaque", "mask", "translucent", "custom"};

// 0x71024d0778
const char* const sDisplayFaceTypeNames[] = {"both", "front", "back", "none"};

// 0x71024d0798
const char* const sBlendModeNames[] = {"none", "color", "logic"};

// 0x71024d07b0
const char* const sPriorityHintTypeNames[] = {
    "none", "field_ground", "field_wall", "vr", "player", "npc", "object", "effect",
};

// 0x71024d07f0
const char* const sPassTypeNames[] = {"no_setting", "seal", "xlu_water", "reduced_buffer"};

}  // namespace

// SEAD_SINGLETON_DISPOSER_IMPL without createInstance / deleteInstance: createInstance
// 0x7100c6a95c inlines the constructor, which is not recovered (see the header).
ModelSharedResource::SingletonDisposer_::~SingletonDisposer_() {
    if (this == sStaticDisposer) {
        sStaticDisposer = nullptr;
        ModelSharedResource::sInstance->~ModelSharedResource();
        ModelSharedResource::sInstance = nullptr;
    }
}
ModelSharedResource* ModelSharedResource::sInstance = nullptr;
ModelSharedResource::SingletonDisposer_* ModelSharedResource::SingletonDisposer_::sStaticDisposer =
    nullptr;

ModelSharedResource::~ModelSharedResource() = default;

sead::SafeString ModelSharedResource::getRenderInfoEnvObjSetName() {
    return "gsys_env_obj_set";
}

sead::SafeString ModelSharedResource::getRenderInfoLightName(ModelEnum::LightMapType type) {
    return sLightMapTypeNames[type];
}

sead::SafeString ModelSharedResource::getRenderInfoPassName() {
    return "gsys_pass";
}

sead::SafeString ModelSharedResource::getRenderInfoBoolName(ModelEnum::RenderInfoBool type) {
    return sRenderInfoBoolNames[type];
}

sead::SafeString ModelSharedResource::getRenderInfoStateName(ModelEnum::RenderInfoState type) {
    return sRenderInfoStateNames[type];
}

sead::SafeString ModelSharedResource::getRenderStateModeName(ModelEnum::RenderStateMode mode) {
    return sRenderStateModeNames[mode];
}

sead::SafeString ModelSharedResource::getDisplayFaceTypeName(ModelEnum::DisplayFaceType type) {
    return sDisplayFaceTypeNames[type];
}

sead::SafeString ModelSharedResource::getBlendModeName(ModelEnum::BlendMode mode) {
    return sBlendModeNames[mode];
}

sead::SafeString ModelSharedResource::getRenderInfoPriorityHintName() {
    return "gsys_priority_hint";
}

ModelEnum::PriorityHintType ModelSharedResource::getPriorityHintType(const sead::SafeString& name) {
    for (s32 i = 0; i < 8; ++i) {
        if (name == sead::SafeString(sPriorityHintTypeNames[i]))
            return static_cast<ModelEnum::PriorityHintType>(i);
    }
    return static_cast<ModelEnum::PriorityHintType>(0);
}

sead::SafeString ModelSharedResource::getRenderInfoPriorityName() {
    return "gsys_priority";
}

bool ModelSharedResource::isRenderInfoBoolEnabled(const sead::SafeString& value) {
    return value.cstr()[0] == '1';
}

sead::SafeString ModelSharedResource::getPassTypeName(ModelEnum::PassType type) {
    return sPassTypeNames[type];
}

}  // namespace gsys
