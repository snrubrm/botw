#include "aal/aalListener.h"
#include "aal/aalListenerPoser.h"

namespace aal {

// 0x7100b842fc
Listener::Listener()
    : _58(1.0f), _60(nullptr), mIs2D(false), _ec(1.0f), _f0(false), mPoser(nullptr), _1a8(true), _1ac(0) {
    setObjName("Listener");
    _5c = -1.0f;
}

// 0x7100b84474 (D1) / 0x7100b84494 (D0)
Listener::~Listener() = default;

// NON_MATCHING: same instructions; the previous position is kept in other callee-saved float registers.
// 0x7100b844d4
void Listener::calc() {
    const f32 prev_x = mMatrix.m[0][3];
    const f32 prev_y = mMatrix.m[1][3];
    const f32 prev_z = mMatrix.m[2][3];

    if (mPoser)
        mPoser->calcListenerMatrix(&mLocalMatrix, &mLocalMatrixForAngle);
    else
        mLocalMatrixForAngle = mLocalMatrix;

    // The position of the listener in the space of the matrix for the angle: -(R^T * t).
    const auto& m = mLocalMatrixForAngle.m;
    const f32 x = -(m[0][0] * m[0][3]) - m[1][0] * m[1][3] - m[2][0] * m[2][3];
    const f32 y = -(m[0][3] * m[0][1]) - m[1][3] * m[1][1] - m[2][3] * m[2][1];
    const f32 z = -(m[0][3] * m[0][2]) - m[1][3] * m[1][2] - m[2][3] * m[2][2];
    mPositionForAngle.set(x, y, z);

    mMatrix.setInverse(mLocalMatrix);

    if (_1ac == 0) {
        if (_1a8) {
            _19c = sead::Vector3f::zero;
            _1a8 = false;
        } else {
            const f32 dz = mMatrix.m[2][3] - prev_z;
            const f32 dy = mMatrix.m[1][3] - prev_y;
            const f32 dx = mMatrix.m[0][3] - prev_x;
            _19c.set(dx, dy, dz);
        }
    }

    mDirectivity.setListenerMatrix(mMatrix);
}

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
