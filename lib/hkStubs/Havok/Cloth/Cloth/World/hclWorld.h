#pragma once
#include <Havok/Common/Base/hkBase.h>

class hclClothInstance;

// Constructor140b8f8/table2533570, allocation1218030 and deleting destructor140bc5c
// prove size98. Add/remove retain/release the cloth and notify actual listeners.
class hclWorld : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclWorld)
    ~hclWorld() override;
    void addCloth(hclClothInstance* cloth);
    void removeCloth(hclClothInstance* cloth);
private:
    hkArray<hclClothInstance*> m_clothInstances;
    // Additional arrays, listener interface and mutex lifetime remain unrecovered.
    hkUint8 _20[0x98 - 0x20];
};
static_assert(sizeof(hclWorld) == 0x98);
