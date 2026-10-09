#pragma once

#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalMemoryPool.h"

namespace aal {

/// Attaches and detaches memory pools from the audio hardware.
class MemoryPoolManager {
public:
    MemoryPoolManager();
    // Native vtable 0x71024C4A58 contains the two destructor entries.
    virtual ~MemoryPoolManager();

    /// 0x7100b96eac (declared only): adds the pool to the list of the pools that are attached at the next flush.
    void requestAttachMemoryPool(MemoryPool* pool);
    void requestAttachMemoryPool(MemoryPool* pool, void* memory, size_t size);

    // 0x7100B96F80; returns whether the pool was removed or queued for detachment.
    bool requestDetachMemoryPool(MemoryPool* pool);

private:
    // Constructor 0x7100B96DB4 initializes both node offsets to 0x58.
    // Attach and release routines independently consume these offset lists.
    sead::OffsetList<MemoryPool> mAcquireRequests;
    sead::OffsetList<MemoryPool> mReleaseRequests;
    sead::CriticalSection mCriticalSection;
    // System initializer 0x7100B79844 allocates 0x78a8 bytes. The trailing
    // fixed-list storage is not used by the retail request routines.
    u8 _78[0x78a8 - 0x78];
};
static_assert(sizeof(MemoryPoolManager) == 0x78a8);

}  // namespace aal
