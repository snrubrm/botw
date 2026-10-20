#pragma once

inline void hkVector4fComparison::setAnd(hkVector4fComparisonParameter a,
                                         hkVector4fComparisonParameter b) {
    m_mask = a.m_mask & b.m_mask;
}

inline void hkVector4fComparison::setAndNot(hkVector4fComparisonParameter a,
                                            hkVector4fComparisonParameter b) {
    m_mask = a.m_mask & ~b.m_mask;
}

inline void hkVector4fComparison::setXor(hkVector4fComparisonParameter a,
                                         hkVector4fComparisonParameter b) {
    m_mask = a.m_mask ^ b.m_mask;
}

inline void hkVector4fComparison::setOr(hkVector4fComparisonParameter a,
                                        hkVector4fComparisonParameter b) {
    m_mask = a.m_mask | b.m_mask;
}

inline void hkVector4fComparison::setNot(hkVector4fComparisonParameter a) {
    m_mask = ~a.m_mask;
}

inline void hkVector4fComparison::setSelect(hkVector4fComparisonParameter comp,
                                            hkVector4fComparisonParameter trueValue,
                                            hkVector4fComparisonParameter falseValue) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    m_mask = vbslq_u32(comp.m_mask, trueValue.m_mask, falseValue.m_mask);
#else
    m_mask = (comp.m_mask & trueValue.m_mask) | (comp.m_mask & ~falseValue.m_mask);
#endif
}

template <hkVector4fComparison::Mask m>
inline hkBool32 hkVector4fComparison::allAreSet() const {
    return ((m & MASK_X) == 0 || m_mask[0] != 0) && ((m & MASK_Y) == 0 || m_mask[1] != 0) &&
           ((m & MASK_Z) == 0 || m_mask[2] != 0) && ((m & MASK_W) == 0 || m_mask[3] != 0);
}

inline hkBool32 hkVector4fComparison::allAreSet(hkVector4fComparison::Mask m) const {
    return ((m & MASK_X) == 0 || m_mask[0] != 0) && ((m & MASK_Y) == 0 || m_mask[1] != 0) &&
           ((m & MASK_Z) == 0 || m_mask[2] != 0) && ((m & MASK_W) == 0 || m_mask[3] != 0);
}

template <hkVector4fComparison::Mask m>
inline hkBool32 hkVector4fComparison::anyIsSet() const {
    return ((m & MASK_X) != 0 && m_mask[0] != 0) || ((m & MASK_Y) != 0 && m_mask[1] != 0) ||
           ((m & MASK_Z) != 0 && m_mask[2] != 0) || ((m & MASK_W) != 0 && m_mask[3] != 0);
}

inline hkBool32 hkVector4fComparison::anyIsSet(Mask m) const {
    return ((m & MASK_X) != 0 && m_mask[0] != 0) || ((m & MASK_Y) != 0 && m_mask[1] != 0) ||
           ((m & MASK_Z) != 0 && m_mask[2] != 0) || ((m & MASK_W) != 0 && m_mask[3] != 0);
}

inline int hkVector4fComparison::getMask() const {
#ifdef HK_VECTOR4F_AARCH64_NEON
    const m128u bits = {1, 2, 4, 8};
    const m128u masked = m_mask & bits;
    uint32x2_t sum = vpadd_u32(vget_low_u32(masked), vget_high_u32(masked));
    sum = vpadd_u32(sum, sum);
    return vget_lane_u32(sum, 0);
#else
    return (m_mask[0] & MASK_X) | (m_mask[1] & MASK_Y) |
           (m_mask[2] & MASK_Z) | (m_mask[3] & MASK_W);
#endif
}
