#include <Havok/Common/Base/Math/hkMath.h>
#include <Havok/Common/Base/Math/Matrix/hkMatrix4f.h>

// NON_MATCHING: the compiler pairs the last A column with the previous load,
// saving one load and 8 bytes over the original.
void hkMatrix4f::setMul(const hkMatrix4f& a, const hkMatrix4f& b) {
    const hkVector4f a0 = a.m_col0;
    const hkVector4f a1 = a.m_col1;
    const hkVector4f a2 = a.m_col2;
    hkVector4f col;

    col.setMul(a0, b.m_col3.getX());
    col.addMul(a1, b.m_col3.getY());
    col.addMul(a2, b.m_col3.getZ());
    const hkVector4f translation = a.m_col3;
    col.add(translation);
    m_col3 = col;

    col.setMul(a0, b.m_col2.getX());
    col.addMul(a1, b.m_col2.getY());
    col.addMul(a2, b.m_col2.getZ());
    m_col2 = col;

    col.setMul(a0, b.m_col1.getX());
    col.addMul(a1, b.m_col1.getY());
    col.addMul(a2, b.m_col1.getZ());
    m_col1 = col;

    col.setMul(a0, b.m_col0.getX());
    col.addMul(a1, b.m_col0.getY());
    col.addMul(a2, b.m_col0.getZ());
    m_col0 = col;
}
