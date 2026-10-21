#include <gsys/gsysG3dResMaterialEx.h>

namespace gsys {

// 0x7100c6d958
const G3dResMaterialEx::ShadingModelInfo* G3dResMaterialEx::getShadingModelObj(
    ModelEnum::ShaderAssignType assign_type) const {
    return ((1u << int(assign_type)) & mMask) ? &mShadingModel : nullptr;
}

s32 G3dResMaterialEx::calcRequiredMemorySize(const nn::g3d::ResMaterial*) {
    return 0x440;
}

}  // namespace gsys
