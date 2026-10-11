#include "aal/aalMemoryPoolManager.h"
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include <nn/atk/detail/driver/HardwareManager.h>

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

// NON_MATCHING: renderer configuration address calculation is scheduled later.
// 0x7100B97090
void MemoryPoolManager::waitForDetachMemoryPool(MemoryPool* pool) {
    if (!pool)
        return;
    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
        for (MemoryPool& request : mAcquireRequests) {
            if (&request == pool) {
                mAcquireRequests.erase(&request);
                return;
            }
        }
    }
    if (nn::audio::IsMemoryPoolAttached(&pool->mPoolType) &&
        nn::audio::RequestDetachMemoryPool(&pool->mPoolType)) {
        auto& hardware = nn::atk::detail::Util::Singleton<
            nn::atk::detail::driver::HardwareManager>::GetInstance();
        if (hardware.IsInitialized()) {
            const auto wait_time = sead::TickSpan::makeFromMilliSeconds(5);
            do {
                sead::Thread::sleep(wait_time);
            } while (nn::audio::IsMemoryPoolAttached(&pool->mPoolType));
            nn::audio::ReleaseMemoryPool(hardware.GetAudioRendererConfig(), &pool->mPoolType);
        }
    }
}

// NON_MATCHING: renderer configuration address calculation differs at loop entry.
// 0x7100B971B8
void MemoryPoolManager::flushMemoryPoolAcquireRequest() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
    if (!mAcquireRequests.isEmpty()) {
        auto& hardware = nn::atk::detail::Util::Singleton<
            nn::atk::detail::driver::HardwareManager>::GetInstance();
        if (hardware.IsInitialized()) {
            for (MemoryPool& pool : mAcquireRequests.robustRange()) {
                if (nn::audio::AcquireMemoryPool(hardware.GetAudioRendererConfig(),
                                                 &pool.mPoolType, pool.memory, pool.size) &&
                    nn::audio::RequestAttachMemoryPool(&pool.mPoolType)) {
                    pool._50 = true;
                }
                mAcquireRequests.erase(&pool);
            }
        }
    }
}

// NON_MATCHING: renderer configuration address calculation differs at loop entry.
// 0x7100B97294
void MemoryPoolManager::flushMemoryPoolReleaseRequest() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCriticalSection);
    if (!mReleaseRequests.isEmpty()) {
        auto& hardware = nn::atk::detail::Util::Singleton<
            nn::atk::detail::driver::HardwareManager>::GetInstance();
        if (hardware.IsInitialized()) {
            for (MemoryPool& pool : mReleaseRequests.robustRange()) {
                if (!nn::audio::IsMemoryPoolAttached(&pool.mPoolType)) {
                    // The native routine queries both values before releasing the pool.
                    nn::audio::GetMemoryPoolAddress(&pool.mPoolType);
                    nn::audio::GetMemoryPoolSize(&pool.mPoolType);
                    nn::audio::ReleaseMemoryPool(hardware.GetAudioRendererConfig(), &pool.mPoolType);
                    mReleaseRequests.erase(&pool);
                }
            }
        }
    }
}

}  // namespace aal
