#pragma once

#include <Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h>
#include <cstddef>

// Partially modelled from the native constructor 0x710157f978 (468 B) and destructor 0x710157fdb8
// (636 B) of the 0x710253a978 vtable group. The native object is 0x1570 bytes: an hkMemoryAllocator
// primary base at +0, the extended interface at +8 (its vtable is the second table of the group,
// group +0xd8), and 42 fixed-size pool allocators between +0x58 and +0x1560 that the constructor
// initializes with the size-class table at 0x710157fb58. Only the shape the game's derived allocator
// (ksys::phys::Unk_710251a370) needs is modelled here; the pool bodies are library rows.
class hkFreeListAllocator : public hkMemoryAllocator, public hkMemoryAllocator::ExtendedInterface {
public:
    hkFreeListAllocator();
    ~hkFreeListAllocator() override;

    // Declared only. The native definitions are the library rows 0x7101580564, 0x7101580744,
    // 0x710158043c, 0x7101588634, 0x7101588640, 0x7101580590, 0x71015807f8, 0x71015801e8,
    // 0x71015803fc, 0x7101580328 and 0x71012b1948.
    void* blockAlloc(int numBytes) override;
    void blockFree(void* p, int numBytes) override;
    void* bufAlloc(int& reqNumBytesInOut) override;
    void bufFree(void* p, int numBytes) override;
    void* bufRealloc(void* pold, int oldNumBytes, int& reqNumBytesInOut) override;
    void blockAllocBatch(void** ptrsOut, int numPtrs, int blockSize) override;
    void blockFreeBatch(void** ptrsIn, int numPtrs, int blockSize) override;
    void getMemoryStatistics(MemoryStatistics& u) const override;
    int getAllocatedSize(const void* obj, int nbytes) const override;
    void resetPeakMemoryStatistics() override;
    hkMemoryAllocator::ExtendedInterface* getExtendedInterface() override;

    // Extended-interface overrides, declared only (the native bodies are the library rows in the
    // 0x7101580c08..0x7101580e84 range and hkFreeListAllocator::isOk 0x7101580374).
    void garbageCollect() override;
    void incrementalGarbageCollect(int numBlocks) override;
    hkResult setMemorySoftLimit(hk_size_t maxMemory) override;
    hk_size_t getMemorySoftLimit() const override;
    bool canAllocTotal(int numBytes) override;
    hkResult walkMemory(MemoryWalkCallback callback, void* param) override;
    hk_size_t getApproxTotalAllocated() const override;
    void setScrubValues(hkUint32 allocValue, hkUint32 freeValue) override;
    int addToSnapshot(hkMemorySnapshot& snap, int parentId) override;
    bool isOk() override;

private:
    hkUint8 _10[0x1570 - 0x10];
};
static_assert(sizeof(hkFreeListAllocator) == 0x1570);
