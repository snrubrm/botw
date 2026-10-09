#pragma once

// Native reflection 177f3c0 lists rotation at 0 and translation at 0x10.
// The cache copy 1531f80 and comparison 15197d0 use these same members.
class hkQTransformf {
public:
    hkQuaternionf m_rotation;
    hkVector4f m_translation;
};
static_assert(sizeof(hkQTransformf) == 0x20);
static_assert(offsetof(hkQTransformf, m_translation) == 0x10);
