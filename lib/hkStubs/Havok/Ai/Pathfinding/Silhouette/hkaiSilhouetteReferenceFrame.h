#pragma once

#include <Havok/Common/Base/hkBase.h>

// Reflection 176e238 names three vectors; producer 15568e8 writes them.
struct hkaiSilhouetteReferenceFrame {
    hkVector4 m_up;
    hkVector4 m_referenceAxis;
    hkVector4 m_orthogonalAxis;
};
static_assert(sizeof(hkaiSilhouetteReferenceFrame) == 0x30);
static_assert(offsetof(hkaiSilhouetteReferenceFrame, m_referenceAxis) == 0x10);
static_assert(offsetof(hkaiSilhouetteReferenceFrame, m_orthogonalAxis) == 0x20);
