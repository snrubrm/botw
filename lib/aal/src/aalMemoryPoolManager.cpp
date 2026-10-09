#include "aal/aalMemoryPoolManager.h"
#include <prim/seadScopedLock.h>

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

// 0x7100B96F80
// NON_MATCHING: early returns produce a single result flag and different block order.
bool MemoryPoolManager::requestDetachMemoryPool(MemoryPool* pool) {
    if (!pool)
        return false;
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
    for (MemoryPool& request : mAcquireRequests) {
        if (&request == pool) {
            mAcquireRequests.erase(&request);
            return true;
        }
    }
    if (pool->node.isLinked() || !pool->mPoolType._0)
        return true;
    if (nn::audio::IsMemoryPoolAttached(&pool->mPoolType) &&
        nn::audio::RequestDetachMemoryPool(&pool->mPoolType)) {
        mReleaseRequests.pushBack(pool);
        return true;
    }
    return false;
}

}  // namespace aal
