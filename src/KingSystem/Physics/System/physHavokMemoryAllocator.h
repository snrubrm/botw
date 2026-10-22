#pragma once

#include <Havok/Common/Base/Memory/Allocator/FreeList/hkFreeListAllocator.h>
#include <Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class ExpHeap;
}

namespace ksys::phys {

class HavokMemoryAllocator : public hkMallocAllocator, public sead::hostio::Node {
public:
    explicit HavokMemoryAllocator(int align = HK_REAL_ALIGNMENT);
    ~HavokMemoryAllocator() override;

    void initDualHeap(sead::Heap* heap1, sead::Heap* heap2, u32 size, const sead::SafeString& name);

    void* blockAlloc(int numBytes) override;
    void blockFree(void* p, int numBytes) override;
    int getAllocatedSize(const void* obj, int nbytes) const override;

    size_t getHeapSize() const;
    size_t getHeapFreeSize() const;

private:
    sead::ExpHeap* mHeap{};
};

// Second Havok memory object System::initMemorySystem creates (vtable 0x710251a370, 0x1578 bytes).
// Its constructor 0x71012b18f0 calls the library hkFreeListAllocator constructor 0x710157f978 (468 B,
// vtable group 0x710253a978) and then installs its own group, which aliases the library's virtuals.
// The trailing u64 at +0x1570 is cleared by the constructor. TODO: incomplete.
class Unk_710251a370 : public hkFreeListAllocator {
public:
    // 0x71012b18f0 (declared only)
    Unk_710251a370();
    ~Unk_710251a370() override;

private:
    u64 _1570{};
};
KSYS_CHECK_SIZE_NX150(Unk_710251a370, 0x1578);

}  // namespace ksys::phys
