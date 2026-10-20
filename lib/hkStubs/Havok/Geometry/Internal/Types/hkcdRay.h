#pragma once
#include <Havok/Common/Base/hkBase.h>

struct hkcdRay {
    hkcdRay() = default;
    // Inline-only in the original: F7EDD8 initializes the same three-vector
    // record consumed by triangle tests, including zero direction handling.
    void setOriginDirection(hkVector4Parameter origin, hkVector4Parameter direction,
                            hkSimdRealParameter fraction) {
        m_origin = origin;
        m_direction.setXYZ_W(direction, fraction);
        const auto zeroDirection = m_direction.equalZero();
        m_direction.zeroIfTrue(zeroDirection);
        m_invDirection.setReciprocal(m_direction);
        hkVector4 max;
        max.setAll(HK_REAL_MAX);
        m_invDirection.setSelect(zeroDirection, max, m_invDirection);
        m_invDirection.setInt24W(m_direction.greaterEqualZero().getMask() &
                                hkVector4Comparison::MASK_XYZ);
    }

    hkVector4 m_origin;
    hkVector4 m_direction;
    hkVector4 m_invDirection;
};
static_assert(sizeof(hkcdRay) == 0x30);
