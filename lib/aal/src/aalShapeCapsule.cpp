#include <geom/seadCapsule.h>
#include <geom/seadGeometry.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadRendering.h>
#include <math/seadMathCalcCommon.h>
#include "aal/aalShape.h"
#include "aal/aalShapeMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9abd4
ShapeCapsule* ShapeCapsule::create(const sead::SafeString& name, sead::Heap* heap) {
    auto* shape = new (heap, 8) ShapeCapsule(name);
    SystemAccessor::getShapeMgr()->addShape(shape);
    return shape;
}

// NON_MATCHING: same arithmetic, different schedule (and the max is fmaxnm instead of fmax)
// 0x7100b9ac68
void ShapeCapsule::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                                 bool position_at_bottom) {
    const f32 radius = vector.x * 0.5f;
    setRadius(radius);

    sead::Matrix34f matrix;
    matrix.makeR(rotation);

    // The segment is the part of the capsule between the centers of the two caps.
    const f32 length = sead::Mathf::max(vector.y - vector.x, 0.0f);
    if (length == 0.0f) {
        setVector(sead::Vector3f::zero);
    } else {
        sead::Vector3f axis;
        axis.setMul(matrix, sead::Vector3f::ey * length);
        setVector(axis);
    }

    sead::Vector3f center_offset;
    if (position_at_bottom)
        center_offset = sead::Vector3f::ey * radius;
    else
        center_offset = sead::Vector3f::ey * -0.5f * length;
    mOffset.setMul(matrix, center_offset);
}

// NON_MATCHING: same arithmetic, different schedule
// 0x7100b9aef8
void ShapeCapsule::calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const {
    if (!out)
        return;

    sead::Vector3f position;
    getPositionWithOffset(&position);

    sead::Vector3f closest = position;
    if (!(mVector.x == 0.0f && mVector.y == 0.0f && mVector.z == 0.0f)) {
        sead::Matrix34f rotation = mMatrix;
        rotation.setTranslation(sead::Vector3f::zero);
        const sead::Vector3f direction = rotation * mVector;

        const sead::Segment3f segment(position, position + direction);
        f32 ratio;
        sead::Geometry::calcSquaredDistancePointToSegment(source, segment, &ratio);
        closest = position + direction * ratio;
    }

    const sead::Vector3f diff = source - closest;
    const f32 distance = diff.length();
    if (distance <= mRadius)
        *out = source;
    else
        *out = closest + diff * (mRadius / distance);
}

// NON_MATCHING: same arithmetic, different schedule
// 0x7100b9b0e0
void ShapeCapsule::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color, f32 scale) const {
    sead::Vector3f position;
    getPositionWithOffset(&position);

    sead::Matrix34f rotation = mMatrix;
    rotation.setTranslation(sead::Vector3f::zero);
    const sead::Vector3f direction = rotation * mVector;

    const sead::Segment3f segment(position, position + direction);
    sead::Rendering::draw(&drawer, sead::Capsule3f(segment, getRadius()), color);
}

}  // namespace aal
