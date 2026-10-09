#pragma once

#include "aal/aalMemoryPool.h"

namespace aal {

/// Attaches and detaches memory pools from the audio hardware.
class MemoryPoolManager {
public:
    /// 0x7100b96eac (declared only): adds the pool to the list of the pools that are attached at the next flush.
    void requestAttachMemoryPool(MemoryPool* pool);

    // 0x7100B96F80; returns whether the pool was removed or queued for detachment.
    bool requestDetachMemoryPool(MemoryPool* pool);
};

}  // namespace aal
