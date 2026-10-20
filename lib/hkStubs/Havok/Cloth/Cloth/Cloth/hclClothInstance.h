#pragma once
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Cloth/Cloth/Cloth/hclClothData.h>
#include <Havok/Cloth/Cloth/SimCloth/hclSimClothInstance.h>

class hclAction;

// Factory14169d0 allocates60 and invokes140e51c; native table25336d0.
class hclClothInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclClothInstance)
    ~hclClothInstance() override;
    // Native 140ef14 retains an action before adding it to +0x50;
    // 140efac removes it without preserving order, then releases it.
    void addAction(hclAction* action);
    void removeAction(hclAction* action);
    hclClothData* m_clothData;
    hkInt32 m_currentState;
    hkReal _1c;
    hkArray<Unk_71025335A8*> m_simClothInstances;
private:
    hkUint8 _30[0x50 - 0x30];
public:
    // Constructor 140e51c initializes the actual hkArray at +0x50.
    hkArray<hclAction*> m_actions;
};
static_assert(sizeof(hclClothInstance) == 0x60);
static_assert(offsetof(hclClothInstance, m_actions) == 0x50);
