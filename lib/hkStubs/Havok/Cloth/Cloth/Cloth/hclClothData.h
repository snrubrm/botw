#pragma once
#include <Havok/Common/Base/hkBase.h>

// Reflection140b610 names hclClothData, size80. Other owned fields are unrecovered.
class hclClothData : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclClothData)
    ~hclClothData() override;
    hkStringPtr m_name;
private:
    hkUint8 _18[0x80 - 0x18];
};
static_assert(sizeof(hclClothData) == 0x80);
