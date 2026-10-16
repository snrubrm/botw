#pragma once

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

// Placeholder name (vtable 0x710251a370, 0x1578 bytes): the second Havok memory object System::initMemorySystem
// creates (its constructor 0x71012b18f0 calls a Havok base constructor 0x710157f978). TODO: incomplete.
class Unk_710251a370 {
public:
    // 0x71012b18f0 (declared only)
    Unk_710251a370();

    u8 _0[0x1578];
};
KSYS_CHECK_SIZE_NX150(Unk_710251a370, 0x1578);

}  // namespace ksys::phys
