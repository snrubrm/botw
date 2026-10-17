#pragma once
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Cloth/Cloth/Collidable/hclCollidable.h>
#include <Havok/Cloth/Cloth/SimCloth/hclSimClothData.h>

// Real runtime object: factory14100f4 allocates1e0, constructor140c694/table25335a8.
// Its original class name is unrecovered. Constructor clones retained collidables
// into+d0; destructor140cae0 releases them. Other owned state remains unmodelled.
class Unk_71025335A8 : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(Unk_71025335A8)
    ~Unk_71025335A8() override;
    hclSimClothData* m_simClothData;
private:
    hkUint8 _18[0xd0 - 0x18];
public:
    hkArray<hclCollidable*> m_collidables;
private:
    hkUint8 _e0[0x1e0 - 0xe0];
};
static_assert(sizeof(Unk_71025335A8) == 0x1e0);
static_assert(offsetof(Unk_71025335A8, m_collidables) == 0xd0);
