#include <gsys/gsysG3dResMaterialEx.h>
#include <prim/seadStringUtil.h>

namespace gsys {

// 0x7100c6d974
bool G3dResMaterialEx::isShaderOptionBool(const sead::SafeString& name) const {
    const char* option = getShaderOption(name);
    if (!option)
        return false;
    s32 value;
    if (!sead::StringUtil::tryParseS32(&value, sead::SafeString(option),
                                       sead::StringUtil::CardinalNumber::BaseAuto))
        return false;
    return value != 0;
}

// 0x7100c6d958
const G3dResMaterialEx::ShadingModelInfo* G3dResMaterialEx::getShadingModelObj(
    ModelEnum::ShaderAssignType assign_type) const {
    return ((1u << int(assign_type)) & mMask) ? &mShadingModel : nullptr;
}

s32 G3dResMaterialEx::calcRequiredMemorySize(const nn::g3d::ResMaterial*) {
    return 0x440;
}

}  // namespace gsys
