#pragma once
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Cloth/Cloth/Cloth/hclClothData.h>
#include <Havok/Cloth/Cloth/SimCloth/hclSimClothInstance.h>

// Factory14169d0 allocates60 and invokes140e51c; native table25336d0.
class hclClothInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclClothInstance)
    ~hclClothInstance() override;
    hclClothData* m_clothData;
    hkInt32 m_currentState;
    hkReal _1c;
    hkArray<Unk_71025335A8*> m_simClothInstances;
private:
    hkUint8 _30[0x60 - 0x30];
};
static_assert(sizeof(hclClothInstance) == 0x60);
