#include <math/seadMathCalcCommon.h>
#include "aal/aalShape.h"
#include "aal/aalShapeMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9bbc0
ShapeCylinder* ShapeCylinder::create(const sead::SafeString& name, sead::Heap* heap) {
    auto* shape = new (heap, 8) ShapeCylinder(name);
    SystemAccessor::getShapeMgr()->addShape(shape);
    return shape;
}

// NON_MATCHING: same arithmetic, different schedule
// 0x7100b9bc54
void ShapeCylinder::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                                  bool position_at_bottom) {
    setRadius(vector.x * 0.5f);

    sead::Matrix34f matrix;
    matrix.makeR(rotation);

    const f32 length = sead::Mathf::max(vector.y, 0.0f);
    if (length == 0.0f) {
        setVector(sead::Vector3f::zero);
    } else {
        sead::Vector3f axis;
        axis.setMul(matrix, sead::Vector3f::ey * length);
        setVector(axis);
    }

    if (position_at_bottom) {
        mOffset = sead::Vector3f::zero;
    } else {
        sead::Vector3f center_offset = sead::Vector3f::ey * -0.5f * length;
        mOffset.setMul(matrix, center_offset);
    }
}

}  // namespace aal
