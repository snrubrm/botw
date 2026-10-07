#pragma once

#include "aal/aalMemoryPool.h"

namespace aal {

/// Attaches the memory pools to the audio hardware. TODO: only requestAttachMemoryPool is declared.
class MemoryPoolManager {
public:
    /// 0x7100b96eac (declared only): adds the pool to the list of the pools that are attached at the next flush.
    void requestAttachMemoryPool(MemoryPool* pool);
};

}  // namespace aal
