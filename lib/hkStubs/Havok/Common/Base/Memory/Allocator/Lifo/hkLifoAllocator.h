#pragma once

#include <Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h>

class hkLifoAllocator : public hkMemoryAllocator {
public:
    explicit hkLifoAllocator(int slabSize = 32 * 1024);

    void init(hkMemoryAllocator* slabAllocator, hkMemoryAllocator* largeAllocator,
              hkMemoryAllocator* internalAllocator);
    /// Optional: [slabAllocator, largeAllocator, internalAllocator]
    void quit(hkMemoryAllocator* allocators[3] = nullptr);

    void* blockAlloc(int numBytes) override;

    /// Inline equivalent of blockAlloc
    HK_FORCE_INLINE void* fastBlockAlloc(int numBytes);

    void blockFree(void* p, int numBytes) override;

    /// Inline equivalent of blockFree
    HK_FORCE_INLINE void fastBlockFree(void* p, int numBytes);

    void* bufAlloc(int& reqNumBytesInOut) override;
    void bufFree(void* p, int numBytes) override;
    void* bufRealloc(void* pold, int oldNumBytes, int& reqNumBytesInOut) override;

    void getMemoryStatistics(MemoryStatistics& u) const override {}
    int getAllocatedSize(const void* obj, int nbytes) const override { return nbytes; }

    bool isEmpty() const;
    int numExternalAllocations() const;

protected:
    void* allocateFromNewSlab(int nbytes);
    void popNonLifoFrees();
    void slowBlockFree(void*, int numBytesIn);
    void insertNonLifoFree(void* p, int nbytes);

    class Implementation;

    Implementation* m_impl;

    const int m_slabSize;

    void* m_cur;
    void* m_end;
    void* m_firstNonLifoEnd;

    void* m_cachedEmptySlab;

    hkMemoryAllocator* m_slabAllocator;
    hkMemoryAllocator* m_largeAllocator;
    hkMemoryAllocator* m_internalAllocator;
};

// Inlined by the local arrays in CharacterRigidBody::getSupportInfo F69190.
HK_FORCE_INLINE void* hkLifoAllocator::fastBlockAlloc(int numBytes) {
    const int aligned_size = (numBytes + 15) & ~15;
    char* next = static_cast<char*>(m_cur) + aligned_size;
    if (aligned_size > m_slabSize || next > m_end)
        return allocateFromNewSlab(aligned_size);
    void* block = m_cur;
    m_cur = next;
    return block;
}

HK_FORCE_INLINE void hkLifoAllocator::fastBlockFree(void* p, int numBytes) {
    const int aligned_size = (numBytes + 15) & ~15;
    if (numBytes <= m_slabSize && static_cast<char*>(p) + aligned_size == m_cur &&
        p != m_firstNonLifoEnd) {
        m_cur = p;
    } else {
        slowBlockFree(p, numBytes);
    }
}
