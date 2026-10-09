#pragma once

#include "aal/aalMemoryPool.h"

namespace aal {

/// Attaches the memory pools to the audio hardware. TODO: only requestAttachMemoryPool is declared.
class MemoryPoolManager {
public:
    /// 0x7100b96eac (declared only): adds the pool to the list of the pools that are attached at the next flush.
    void requestAttachMemoryPool(MemoryPool* pool);

    // 0x7100B96F80; AudioResource's native destructor passes its pool member.
    void requestDetachMemoryPool(MemoryPool* pool);
};

}  // namespace aal
