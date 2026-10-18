#pragma once
#include <Havok/Common/Base/hkBase.h>

class hclShape;

// Reflection1437f74: referenced-object parent, size90 and eight members at2534a78.
class hclCollidable : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclCollidable)
    ~hclCollidable() override;

    hkStringPtr m_name;
    hkTransform m_transform;
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
    hkBool m_pinchDetectionEnabled;
    hkInt8 m_pinchDetectionPriority;
    hkReal m_pinchDetectionRadius;
    // Clone1434a20 and destructor1217e94 retain/release this non-null shape.
    hclShape* m_shape;
};
static_assert(sizeof(hclCollidable) == 0x90);
static_assert(offsetof(hclCollidable, m_shape) == 0x88);
