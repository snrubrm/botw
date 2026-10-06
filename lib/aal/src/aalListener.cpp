#include "aal/aalListener.h"

namespace aal {

// 0x7100b84474 (D1) / 0x7100b84494 (D0)
Listener::~Listener() = default;

// 0x7100b8469c
void Listener::setPoser(ListenerPoser* poser) {
    mPoser = poser;
}

// 0x7100b846a4
void Listener::calcLocalPosition(sead::Vector3f* out, const sead::Vector3f& position) const {
    out->setMul(mLocalMatrix, position);
    if (mIs2D)
        out->z = 0.0f;
}

// NON_MATCHING: same arithmetic; the original loads the 2D transform in another order (it computes x and y of the
// transformed position with the operands swapped).
// 0x7100b84748
f32 Listener::calcLocalDistance(const sead::Vector3f& position) const {
    sead::Vector3f local;
    if (mIs2D) {
        local.setMul(mLocalMatrix, position);
        local.z = 0.0f;
    } else {
        local = position - sead::Vector3f(mMatrix.m[0][3], mMatrix.m[1][3], mMatrix.m[2][3]);
    }
    return local.length();
}

// NON_MATCHING: the original copies the whole selected matrix into vector registers (ldp q) and extracts the lanes, here
// the elements are loaded one by one.
// 0x7100b84804
void Listener::calcLocalPositionForAngle(sead::Vector3f* out, const sead::Vector3f& position) const {
    const sead::Matrix34f matrix = _f0 ? mLocalMatrixForAngle : mLocalMatrix;
    out->setMul(matrix, position);
    if (mIs2D)
        out->z = 0.0f;
}

// NON_MATCHING: same vector code, but the original selects the basis with `csel ..., eq` (first operand the plain
// matrix) where this builds `ne` with the operands swapped (the select of the flag at 0xf0 is canonicalised).
// 0x7100b848a0
void Listener::calcLocalMatrixForAngle(sead::Matrix34f* out, const sead::Matrix34f& matrix) const {
    const sead::Matrix34f& basis = !_f0 ? mLocalMatrix : mLocalMatrixForAngle;
    out->setMul(basis, matrix);
    if (mIs2D)
        out->m[2][3] = 0.0f;
}

// 0x7100b84930
void Listener::setObjName(const sead::SafeString& name) {
    mFixedName.copy(name);
    mName = mFixedName;
}

}  // namespace aal
