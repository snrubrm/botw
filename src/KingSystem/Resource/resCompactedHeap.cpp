#include "KingSystem/Resource/resCompactedHeap.h"
#include <atomic>
#include <prim/seadScopedLock.h>

namespace ksys::res {

CompactedHeap::~CompactedHeap() = default;

void CompactedHeap::Unk3::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry.setPointer(ptr);
}

void CompactedHeap::Unk1::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry.setPointer(ptr);
}

CompactedHeap* CompactedHeap::create(const sead::SafeString& name, void* buffer,
                                     size_t buffer_size, u32 x) {
    return new (buffer) CompactedHeap(name, buffer, buffer_size, x);
}

void CompactedHeap::destroy() {
    auto lock = sead::makeScopedLock(_5cf8);
    auto lock2 = sead::makeScopedLock(_5d78);
    this->~CompactedHeap();
}

void CompactedHeap::incrementCompactionCount() {
    mCompactionCount.increment();
}

bool CompactedHeap::setBuffer(void* buffer, size_t size) {
    auto lock = sead::makeScopedLock(_5d38);
    if (_5c90 != 3)
        return false;

    _5cb8 = 0;
    mCompactionCount.exchange(0);
    _5c98 = buffer;
    _5ca0 = size;
    return true;
}

bool CompactedHeap::compact() {
    auto lock = sead::makeScopedLock(_5d38);
    switch (_5c90) {
    case 0:
        x_5();
        break;
    case 1:
        x_2();
        break;
    case 2:
        x_3();
        break;
    case 3:
        if (!_5c98 || !x_4())
            return false;
        x_5();
        break;
    }
    return true;
}

void CompactedHeap::Allocation::sub_71012B8C7C() {
    if (mData) {
        auto* heap = reinterpret_cast<CompactedHeap*>(mTaggedHeap & ~u64(3));
        heap->_5cf8.lock();
        sub_71012B8A78(false);
        mTaggedHeap &= ~u64(1);
        heap->_5cf8.unlock();
    } else {
        mTaggedHeap &= ~u64(1);
    }
}

// NON_MATCHING: the two tag words are computed in the other order (the original makes the cleared
// word the false arm and the set word the true arm; ours has them swapped). Every instruction and
// value is otherwise the same.
// 0x71012b8ce8 (placeholder name): sets or clears tag bit 1 of the allocation, under the heap lock
// while the allocation has data.
void CompactedHeap::Allocation::sub_71012B8CE8(bool x) {
    if (mData) {
        auto* heap = reinterpret_cast<CompactedHeap*>(mTaggedHeap & ~u64(3));
        heap->_5cf8.lock();
        mTaggedHeap = x ? (mTaggedHeap | 2) : (mTaggedHeap & ~u64(2));
        heap->_5cf8.unlock();
    } else {
        mTaggedHeap = x ? (mTaggedHeap | 2) : (mTaggedHeap & ~u64(2));
    }
}

// NON_MATCHING: the call to CompactedHeap::x passes an argument its body never reads; the original
// drops the argument setup because that function is in this TU, and our build only declares it. The
// block-record scan is also strength-reduced to a 64-bit induction variable here.
// 0x71012b8a78 (placeholder name): records the in-use state of this allocation in its block
// record and in the allocation header while the heap lock is held.
void CompactedHeap::Allocation::sub_71012B8A78(bool x) {
    auto* heap = reinterpret_cast<CompactedHeap*>(mTaggedHeap & ~u64(3));
    auto* data = static_cast<u8*>(mData);

    if (data < heap->_5ce8 || data >= heap->_5cf0 + sizeof(Header)) {
        // The data block is outside the heap's own range: find its block record by address.
        const u32 count = heap->_5cb8;
        if (!count)
            return;
        for (s32 i = 0; i < count; ++i) {
            auto* block = heap->getBlock(i);
            if (!block->mInUse)
                continue;
            if (block->mData != mData)
                continue;
            {
                auto lock = sead::makeScopedLock(block->mLock);
                std::atomic_thread_fence(std::memory_order_seq_cst);
                block->mState = x;
            }
            return;
        }
        return;
    }

    auto* header = reinterpret_cast<Header*>(data - *reinterpret_cast<u16*>(data - 2));
    if (!header || header->mMagic != Header::cMagic) {
        // The original only has a debug check in this scope in release builds.
        {
            auto lock = sead::makeScopedLock(heap->_5cf8);
        }
        reinterpret_cast<CompactedHeap*>(mTaggedHeap)->x(this, true);
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    const u8 index = header->mBlockIndex;
    if (index) {
        auto* block = heap->getBlock(index - 1);
        {
            auto lock = sead::makeScopedLock(block->mLock);
            std::atomic_thread_fence(std::memory_order_seq_cst);
            if (index == header->mBlockIndex)
                block->mState = x;
        }
    }
    header->mInUse = x;
}

bool CompactedHeap::Allocation::sub_71012B8C10() {
    if (mData) {
        auto* heap = reinterpret_cast<CompactedHeap*>(mTaggedHeap & ~u64(3));
        heap->_5cf8.lock();
        sub_71012B8A78(true);
        mTaggedHeap |= 1;
        heap->_5cf8.unlock();
    } else {
        mTaggedHeap |= 1;
    }
    return true;
}

}  // namespace ksys::res
