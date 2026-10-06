#include <gfx/seadPrimitiveRenderer.h>
#include <math/seadMathCalcCommon.h>
#include "aal/aalShape.h"
#include "aal/aalShapeMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b9b438
ShapeCube* ShapeCube::create(const sead::SafeString& name, sead::Heap* heap) {
    auto* shape = new (heap, 8) ShapeCube(name);
    SystemAccessor::getShapeMgr()->addShape(shape);
    return shape;
}

// 0x7100b9b49c
void ShapeCube::setSize(const sead::Vector3f& size) {
    if (size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f)
        mVector = size;
}

// NON_MATCHING: the rotation matrix is built identically, only the schedule of the offset calculation differs
// 0x7100b9b4d8
void ShapeCube::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                              bool position_at_bottom) {
    setSize(vector);

    sead::Matrix34f matrix;
    matrix.makeR(rotation);
    setRotate(matrix);

    if (position_at_bottom) {
        sead::Vector3f up;
        up.setMul(matrix, sead::Vector3f::ey);
        mOffset = up * (vector.y * 0.5f);
    } else {
        mOffset = sead::Vector3f::zero;
    }
}

// NON_MATCHING: the transform of the clamped point is scheduled differently (same arithmetic)
// 0x7100b9b6dc
void ShapeCube::calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const {
    if (!out)
        return;

    sead::Vector3f position;
    getPositionWithOffset(&position);
    sead::Matrix34f matrix = mMatrix;
    matrix.setTranslation(position);

    sead::Matrix34f inverse;
    inverse.setInverse(matrix);
    sead::Vector3f local = inverse * source;

    sead::Vector3f half = mVector * 0.5f;
    if (sead::Mathf::abs(local.x) <= half.x && sead::Mathf::abs(local.y) <= half.y &&
        sead::Mathf::abs(local.z) <= half.z) {
        *out = source;
    } else {
        if (local.x < -half.x)
            local.x = -half.x;
        else if (local.x > half.x)
            local.x = half.x;
        if (local.y < -half.y)
            local.y = -half.y;
        else if (local.y > half.y)
            local.y = half.y;
        if (local.z < -half.z)
            local.z = -half.z;
        else if (local.z > half.z)
            local.z = half.z;
        *out = matrix * local;
    }
}

// NON_MATCHING: the original first fills the CubeArg colors with Color4f::cWhite (dead stores that stay in the original)
// 0x7100b9b900
void ShapeCube::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color, f32 scale) const {
    sead::Vector3f position;
    getPositionWithOffset(&position);
    sead::Matrix34f matrix = mMatrix;
    matrix.setTranslation(position);

    const sead::Matrix34f* previous = drawer.getModelMatrix();
    drawer.setModelMatrix(&matrix);
    drawer.drawWireCube(sead::PrimitiveDrawer::CubeArg(sead::Vector3f::zero, mVector, color));
    drawer.setModelMatrix(previous);
}

// 0x7100b9bb4c
void ShapeCube::setVector(const sead::Vector3f& vector) {
    if (vector.x >= 0.0f && vector.y >= 0.0f && vector.z >= 0.0f)
        mVector = vector;
}

}  // namespace aal
