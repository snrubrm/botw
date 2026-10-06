#include "aal/aalCone.h"
#include <math/seadMathCalcCommon.h>

namespace aal {

namespace {

bool isZero(const sead::Vector3f& v) {
    return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
}

f32 calcAngleBetween(const sead::Vector3f& direction, const sead::Vector3f& vector) {
    if (isZero(direction) || isZero(vector))
        return 0.0f;
    f32 dot = direction.dot(vector);
    f32 sin = direction.cross(vector).length();
    return atan2f(sin, dot);
}

}  // namespace

// NON_MATCHING: same stores, only the order of the last three differs
// 0x7100b8db30
Cone::Cone() : mDirection(sead::Vector3f::zero) {
    mAngleStart = sead::Mathf::pi() / 16;
    mAngleEnd = sead::Mathf::pi() / 8;
    mAngleRange = sead::Mathf::pi() / 16;
    mMatrix.makeZero();
}

// 0x7100b8db88
void Cone::setActorMatrix(const sead::Matrix34f& matrix) {
    mMatrix = matrix;
    sead::Vector3f translation;
    mMatrix.getTranslation(translation);
    mDirection = mMatrix * sead::Vector3f(0.0f, 0.0f, 1.0f) - translation;
}

// 0x7100b8dc10
void Cone::getPosition(sead::Vector3f* out) const {
    if (out)
        mMatrix.getTranslation(*out);
}

// NON_MATCHING: the original min/max compile to fmin/fmax (not fminnm/fmaxnm); the clamping itself is the same
// 0x7100b8dc30
void Cone::setAngle(f32 start, f32 end) {
    end = sead::Mathf::min(sead::Mathf::max(end, 0.0f), sead::Mathf::pi());
    start = sead::Mathf::max(start, 0.0f);
    if (start > end)
        start = end;
    mAngleStart = start;
    mAngleEnd = end;
    mAngleRange = end - start;
}

// 0x7100b8dc64
f32 Cone::calcAngle(const sead::Vector3f& position) const {
    if (isZero(mDirection))
        return 0.0f;
    sead::Vector3f translation;
    mMatrix.getTranslation(translation);
    return calcAngleBetween(mDirection, position - translation);
}

// 0x7100b8dd68
f32 Cone::calcRate(const sead::Vector3f& position) const {
    f32 angle = calcAngle(position);
    if (mAngleStart >= angle)
        return 0.0f;
    if (mAngleEnd < angle)
        return 1.0f;
    return (angle - mAngleStart) / mAngleRange;
}

// NON_MATCHING: operand order of the cross product / dot product differs
// 0x7100b8ddbc
f32 Cone::calcRateOriginShiftPos(const sead::Vector3f& position) const {
    f32 angle = calcAngleBetween(mDirection, position);
    if (mAngleStart >= angle)
        return 0.0f;
    if (mAngleEnd < angle)
        return 1.0f;
    return (angle - mAngleStart) / mAngleRange;
}

}  // namespace aal
