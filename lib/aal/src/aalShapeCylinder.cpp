#include <math/seadMathCalcCommon.h>
#include <math/seadQuat.h>
#include <gfx/seadPrimitiveRenderer.h>
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

// NON_MATCHING: native temporary storage and arithmetic scheduling differ.
void ShapeCylinder::calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const {
    if (!out)
        return;
    sead::Vector3f position;
    getPositionWithOffset(&position);
    if (mVector.x == 0.0f && mVector.y == 0.0f && mVector.z == 0.0f) {
        *out = position;
        return;
    }
    sead::Matrix34f rotation = mMatrix;
    rotation.setTranslation(sead::Vector3f::zero);
    sead::Vector3f direction = rotation * mVector;
    const f32 length = direction.normalize();
    sead::Quatf quaternion;
    sead::Matrix34f matrix;
    if (quaternion.makeVectorRotation(sead::Vector3f::ey, direction)) {
        matrix.makeQT(quaternion, position);
    } else {
        // Opposite axes use a half turn around X.
        matrix.setBase(0, sead::Vector3f::ex);
        matrix.setBase(1, -sead::Vector3f::ey);
        matrix.setBase(2, -sead::Vector3f::ez);
        matrix.setTranslation(position);
    }
    sead::Matrix34f inverse;
    inverse.setInverse(matrix);
    sead::Vector3f local = inverse * source;
    local.y = sead::Mathf::clamp(local.y, 0.0f, length);
    const f32 radius = sead::Vector3f(local.x, 0.0f, local.z).length();
    if (radius > mRadius) {
        const f32 scale = mRadius / radius;
        local.x *= scale;
        local.z *= scale;
    }
    *out = matrix * local;
}

// NON_MATCHING: native temporary storage and arithmetic scheduling differ.
void ShapeCylinder::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                                f32 scale) const {
    sead::Vector3f position;
    getPositionWithOffset(&position);
    if (mVector.x == 0.0f && mVector.y == 0.0f && mVector.z == 0.0f) {
        drawer.drawSphere8x16(position, scale, color);
        return;
    }
    sead::Matrix34f rotation = mMatrix;
    rotation.setTranslation(sead::Vector3f::zero);
    sead::Vector3f direction = rotation * mVector;
    const sead::Vector3f center = position + direction * 0.5f;
    const f32 length = direction.normalize();
    sead::Quatf quaternion;
    quaternion.makeVectorRotation(sead::Vector3f::ey, direction);
    sead::Matrix34f matrix;
    matrix.makeQT(quaternion, center);
    const sead::Matrix34f* previous = drawer.getModelMatrix();
    drawer.setModelMatrix(&matrix);
    drawer.drawCylinder32(sead::Vector3f::zero, mRadius, length, color);
    drawer.setModelMatrix(previous);
}

}  // namespace aal
