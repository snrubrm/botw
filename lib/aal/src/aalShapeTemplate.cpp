#include "aal/aalShapeTemplate.h"

namespace aal {

// 0x7100b9dde0
ShapeTemplate::ShapeTemplate() = default;

// 0x7100b9dedc
void ShapeTemplate::initialize(const sead::SafeString& name, const ShapeParam& param) {
    setObjName(name);
    mParam = param;
}

}  // namespace aal
