#pragma once

#include <Havok/Common/Base/Math/Matrix/hkTransform.h>

// Reflection 176e3c4 names this 0x60-byte struct. Records 255b020
// identify the transform and both velocities; game f7e754 independently
// consumes the transform at NavMeshInstance + 0x70.
struct hkaiReferenceFrame {
    hkTransform m_transform;
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
};
static_assert(sizeof(hkaiReferenceFrame) == 0x60);
static_assert(offsetof(hkaiReferenceFrame, m_linearVelocity) == 0x40);
static_assert(offsetof(hkaiReferenceFrame, m_angularVelocity) == 0x50);
