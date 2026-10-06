#include <gfx/seadPrimitiveRenderer.h>
#include "aal/aalShape.h"
#include "aal/aalShapeMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9d918
ShapeSphere* ShapeSphere::create(const sead::SafeString& name, sead::Heap* heap) {
    auto* shape = new (heap, 8) ShapeSphere(name);
    SystemAccessor::getShapeMgr()->addShape(shape);
    return shape;
}

// NON_MATCHING: same arithmetic, different association/schedule of the offset multiplication
// 0x7100b9da84
void ShapeSphere::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                                bool position_at_bottom) {
    f32 radius = vector.x * 0.5f;
    setRadius(radius);
    if (position_at_bottom) {
        sead::Vector3f up = sead::Vector3f::ey * radius;
        sead::Matrix34f matrix;
        matrix.makeR(rotation);
        mOffset.setMul(matrix, up);
    } else {
        mOffset = sead::Vector3f::zero;
    }
}

// 0x7100b9d994
void ShapeSphere::calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const {
    if (!out)
        return;
    sead::Vector3f position;
    getPositionWithOffset(&position);
    sead::Vector3f diff = source - position;
    f32 distance = diff.length();
    if (distance <= mRadius)
        *out = source;
    else
        *out = diff * (mRadius / distance) + position;
}

// 0x7100b9dc0c
void ShapeSphere::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color, f32 scale) const {
    sead::Vector3f position;
    getPositionWithOffset(&position);
    drawer.drawSphere8x16(position, mRadius, color);
}

}  // namespace aal
