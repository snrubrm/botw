#pragma once

// Affine 4x4 helpers. Native 0x710158e938 multiplies two affine matrices and
// 0x710158eabc multiplies the inverse of the first by the second; both are
// used heavily by the Havok world and vehicle code.
class hkMatrix4f {
public:
    void setMul(const hkMatrix4f& a, const hkMatrix4f& b);
    void setMulInverse(const hkMatrix4f& a, const hkMatrix4f& b);

    hkVector4f m_col0;
    hkVector4f m_col1;
    hkVector4f m_col2;
    hkVector4f m_col3;
};
