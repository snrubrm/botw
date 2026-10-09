#include "aal/aalMemoryPoolManager.h"

namespace aal {

// 0x7100B96E64
MemoryPoolManager::~MemoryPoolManager() {}

// 0x7100B96EAC
void MemoryPoolManager::requestAttachMemoryPool(MemoryPool* pool) {
    if (!pool)
        return;
    mCriticalSection.lock();
    mAcquireRequests.pushBack(pool);
    mCriticalSection.unlock();
}

// 0x7100B96F14
void MemoryPoolManager::requestAttachMemoryPool(MemoryPool* pool, void* memory, size_t size) {
    if (!pool)
        return;
    pool->memory = memory;
    pool->size = size;
    mCriticalSection.lock();
    mAcquireRequests.pushBack(pool);
    mCriticalSection.unlock();
}

}  // namespace aal
