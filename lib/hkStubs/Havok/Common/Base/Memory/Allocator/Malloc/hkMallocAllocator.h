#pragma once

#include <Havok/Common/Base/hkBase.h>

// 16-byte aligned: ksys::phys::System::initMemorySystem 0x7101214a0c allocates 0x30 bytes (alignment 0x10) for
// HavokMemoryAllocator, whose fields end at 0x28.
class alignas(16) hkMallocAllocator : public hkMemoryAllocator {
public:
    explicit hkMallocAllocator(int align = HK_REAL_ALIGNMENT)
        : m_align(align), m_currentUsed(0), m_peakUse(0) {}

    void* blockAlloc(int numBytes) override;
    void blockFree(void* p, int numBytes) override;

    void getMemoryStatistics(hkMemoryAllocator::MemoryStatistics& u) const override;
    int getAllocatedSize(const void* obj, int nbytes) const override;
    void resetPeakMemoryStatistics() override;

    int m_align;

    static hkMemoryAllocator* m_defaultMallocAllocator;

protected:
    hkUint32 m_unused;
    hkUint32 m_currentUsed;
    hkUint32 m_peakUse;
};
