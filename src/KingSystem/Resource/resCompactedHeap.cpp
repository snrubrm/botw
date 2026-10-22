#include "KingSystem/Resource/resCompactedHeap.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>
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

// NON_MATCHING: our call to CompactedHeap::x passes a zero sync flag (the callee never reads it);
// the original materialises a one, so the original's x body has a codegen-free use of sync. The
// bounds word at +0x5ca8 is also loaded through a materialised address there.
// 0x71012b8a78 (placeholder name): records the in-use state of this allocation in its block
// record and in the allocation header while the heap lock is held.
void CompactedHeap::Allocation::sub_71012B8A78(bool x) {
    auto* heap = reinterpret_cast<CompactedHeap*>(mTaggedHeap & ~u64(3));
    auto* data = static_cast<u8*>(mData);

    if (heap->_5ce8 > data || heap->_5cf0 + sizeof(Header) <= data) {
        // The data block is outside the heap's own range: find its block record by address.
        const u32 count = heap->_5cb8;
        if (!count)
            return;
        for (u32 i = 0; i < count; ++i) {
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
        auto* heap2 = reinterpret_cast<CompactedHeap*>(mTaggedHeap);
        heap2->x(heap2->_5dc0, true);
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

// 0x71012b5900: checks the heap's block and free lists and then compacts the two indexed free
// lists. The name and sync arguments are only read by the original's debug assertions.
void CompactedHeap::x(const sead::SafeString& name, bool sync) {
    auto lock = sead::makeScopedLock(_5cf8);

    // The largest size class keeps 27 x 32 lists, the two indexed trees 32 x 32.
    for (s32 i = 0; i < 27; ++i) {
        for (s32 j = 0; j < 32; ++j) {
            void* ptr = mFreeListTree3.mLists._0[i]._0[j];
            if (!ptr)
                continue;
            const u32 magic = static_cast<Allocation::Header*>(ptr)->mMagic;
            if (magic == Allocation::Header::cMagic || magic == Allocation::Header::cFreeMagic)
                continue;
            // The original only asserts here in debug builds.
            { auto inner = sead::makeScopedLock(_5cf8); }
        }
    }

    for (s32 i = 0; i < 32; ++i) {
        for (s32 j = 0; j < 32; ++j) {
            void* ptr = mFreeListTree.mLists._0[i]._0[j];
            if (!ptr)
                continue;
            const u32 magic = static_cast<Allocation::Header*>(ptr)->mMagic;
            if (magic == Allocation::Header::cMagic || magic == Allocation::Header::cFreeMagic)
                continue;
            // The original only asserts here in debug builds.
            { auto inner = sead::makeScopedLock(_5cf8); }
        }
    }

    FreeListTree32& tree = mFreeListTree;
    if (!tree.mMask)
        return;

    x_7(true);

    // Walk the chain of contiguous blocks.
    auto* block = static_cast<Allocation::Header*>(_5ce0);
    do {
        const u32 magic = block->mMagic;
        if (magic != Allocation::Header::cMagic && magic != Allocation::Header::cFreeMagic) {
            // The original only asserts here in debug builds.
            { auto inner = sead::makeScopedLock(_5cf8); }
        }
        block = block->getNextBlock();
    } while (reinterpret_cast<Allocation::Header*>(_5cf0) != block);

    {
        const u32 mask = tree.mMask;
        const s32 i = sead::BitFlagUtil::countOnBit((mask - 1) & ~mask);
        const u32 mask2 = tree.mMask2[i];
        const s32 j = sead::BitFlagUtil::countOnBit((mask2 - 1) & ~mask2);
        auto* head = static_cast<Allocation::Header*>(tree.mLists._0[i]._0[j]);
        do {
            auto* node = head;
            do {
                const u32 magic = node->mMagic;
                if (magic != Allocation::Header::cMagic &&
                    magic != Allocation::Header::cFreeMagic) {
                    // The original only asserts here in debug builds.
                    { auto inner = sead::makeScopedLock(_5cf8); }
                }
                node = node->getListNext();
            } while (node != head);
            head = x_8(&tree, head, false);
        } while (head);
    }

    {
        const u32 mask = mFreeListTree2.mMask;
        const s32 i = sead::BitFlagUtil::countOnBit((mask - 1) & ~mask);
        const u32 mask2 = mFreeListTree2.mMask2[i];
        const s32 j = sead::BitFlagUtil::countOnBit((mask2 - 1) & ~mask2);
        auto* head = static_cast<Allocation::Header*>(mFreeListTree2.mLists._0[i]._0[j]);
        do {
            auto* node = head;
            do {
                node = node->getListNext();
            } while (node != head);
            head = x_8(&mFreeListTree2, head, false);
        } while (head);
    }
}

// NON_MATCHING: our call to CompactedHeap::x passes a zero sync flag (the callee never reads it);
// the original materialises a one, so the original's x body has a codegen-free use of sync.
// 0x71012b7448 (placeholder name): releases the allocation whose data block starts at `data`,
// moving its size from the heap's free total to its used total.
void CompactedHeap::x_19(void* data, bool sync) {
    auto lock = sead::makeScopedLock(_5cf8);
    if (sync)
        std::atomic_thread_fence(std::memory_order_seq_cst);

    auto* header = Allocation::Header::get(data);
    if (header->mMagic != Allocation::Header::cMagic) {
        // The original locks and unlocks the heap again in this scope before the repair pass.
        { auto inner = sead::makeScopedLock(_5cf8); }
        x(_5dc0, true);
    }

    const u32 size = header->mSize;
    _5db8 -= size;
    _5dbc += size;
    x_9(header);
}


// NON_MATCHING: the abs() tail is scheduled after the seq_cst fence here (the original keeps only the
// asr above it), and clang merges the two header bit writes into one read-modify-write byte store
// where the original writes mInUse and mFlag separately (bfxil / ubfx + bfi).
// 0x71012b77a8 (placeholder name): allocates a block of `size` bytes for `allocation`, then fills
// the allocation record and its block header (the record's low tag bits are copied to the header).
bool CompactedHeap::x_20(Allocation* allocation, size_t size, s32 alignment) {
    auto lock = sead::makeScopedLock(_5cf8);

    void* data;
    {
        auto inner_lock = sead::makeScopedLock(_5cf8);

        s32 align = alignment;
        if (align == 0)
            align = 8;
        align = sead::Mathi::abs(align);
        std::atomic_thread_fence(std::memory_order_seq_cst);

        const auto block = x_13(size, align);
        if (!block.mBlock)
            return false;

        data = x_16(block.mBlock, size, block.mTagged, align);
    }

    if (!data)
        return false;

    allocation->mTaggedHeap = (allocation->mTaggedHeap & u64(3)) | u64(this);
    allocation->mData = data;
    allocation->mSize = size;

    auto* bytes = static_cast<u8*>(data);
    auto* header = reinterpret_cast<Allocation::Header*>(bytes - *reinterpret_cast<u16*>(bytes - 2));
    header->_14 = allocation->_8;
    header->mInUse = allocation->mTaggedHeap & 1;
    header->mFlag = (allocation->mTaggedHeap & 2) >> 1;
    return true;
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
