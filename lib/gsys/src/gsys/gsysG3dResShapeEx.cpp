#include <gsys/gsysG3dResShapeEx.h>
#include <nn/g3d/ResShape.h>

namespace gsys {

// 0x7100c70564
void G3dResShapeEx::calcShaderInfo(ModelEnum::ShaderAssignType, int, ShaderInfo* info) const {
    *info = ShaderInfo{};
}

// 0x7100c6f580
void G3dResShapeEx::setResShape(nn::g3d::ResShape* res_shape) {
    res_shape->set_50(this);
    mResShape = res_shape;
}

}  // namespace gsys
