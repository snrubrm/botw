#include <geom/seadGeometry.h>
#include <gfx/seadPrimitiveRenderer.h>
#include "aal/aalShape.h"
#include "aal/aalShapeMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9cd38
ShapeSegment* ShapeSegment::create(const sead::SafeString& name, sead::Heap* heap) {
    auto* shape = new (heap, 8) ShapeSegment(name);
    SystemAccessor::getShapeMgr()->addShape(shape);
    return shape;
}

// 0x7100b9cdb4
void ShapeSegment::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                                 bool position_at_bottom) {
    sead::Matrix34f matrix;
    matrix.makeR(rotation);

    sead::Vector3f axis;
    axis.setMul(matrix, sead::Vector3f::ey * vector.y);
    setVector(axis);

    if (position_at_bottom)
        mOffset = sead::Vector3f::zero;
    else
        mOffset = matrix * (sead::Vector3f::ey * (vector.y * -0.5f));
}

// NON_MATCHING: same arithmetic, different schedule
// 0x7100b9cfc8
void ShapeSegment::calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const {
    if (!out)
        return;
    if (mVector.x == 0.0f && mVector.y == 0.0f && mVector.z == 0.0f) {
        getPositionWithOffset(out);
        return;
    }

    sead::Vector3f position;
    getPositionWithOffset(&position);

    sead::Matrix34f rotation = mMatrix;
    rotation.setTranslation(sead::Vector3f::zero);
    const sead::Vector3f direction = rotation * mVector;

    const sead::Segment3f segment(position, position + direction);
    f32 ratio;
    sead::Geometry::calcSquaredDistancePointToSegment(source, segment, &ratio);
    *out = position + direction * ratio;
}

// 0x7100b9d148
void ShapeSegment::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color, f32 scale) const {
    if (mVector.x == 0.0f && mVector.y == 0.0f && mVector.z == 0.0f)
        return;

    sead::Vector3f position;
    getPositionWithOffset(&position);

    sead::Matrix34f rotation = mMatrix;
    rotation.setTranslation(sead::Vector3f::zero);
    const sead::Vector3f direction = rotation * mVector;

    drawer.drawLine(position, position + direction, color);
}

}  // namespace aal
