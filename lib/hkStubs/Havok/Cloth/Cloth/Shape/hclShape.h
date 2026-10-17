#pragma once
#include <Havok/Common/Base/hkBase.h>

// Reflection147c994 proves this data prefix/size10 and enum storage at+c.
// Additional shape virtual methods are unrecovered; no vtable is defined here.
class hclShape : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclShape)
    hkInt32 m_type;
};
static_assert(sizeof(hclShape) == 0x10);
