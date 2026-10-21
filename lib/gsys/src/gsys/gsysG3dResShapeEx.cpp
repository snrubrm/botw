#include <gsys/gsysG3dResShapeEx.h>

namespace gsys {

// 0x7100c70564
void G3dResShapeEx::calcShaderInfo(ModelEnum::ShaderAssignType, int, ShaderInfo* info) const {
    *info = ShaderInfo{};
}

}  // namespace gsys
