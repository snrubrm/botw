#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

class DungeonPackMgr;

namespace ksys::res {

// TODO: very incomplete
class CompactedHeap {
public:
    CompactedHeap(const sead::SafeString& name, void* buffer, size_t buffer_size, u32 x);
    static CompactedHeap* create(const sead::SafeString& name, void* buffer, size_t buffer_size,
                                 u32 x);

    // 0x71012b8d70 (CSV CompactedHeap::Unk2::setPointer). Placeholder type: 32 pointers. The source is taken by
    // reference (the original reloads it after every store).
    struct Unk2 {
        void setPointer(void* const& ptr);

        void* _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk2, 0x100);

    // 0x71012b5310 (CSV CompactedHeap::Unk1::setPointer): 27 Unk2 entries.
    struct Unk1 {
        void setPointer(void* const& ptr);

        Unk2 _0[27];
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x1b00);

    // 0x71012b8e74 (CSV CompactedHeap::Unk4::setPointer): same shape as Unk2 (placeholder type).
    struct Unk4 {
        void setPointer(void* const& ptr);

        void* _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk4, 0x100);

    // 0x71012b5490 (CSV agl::sdw::PrimitiveOcclusion::calcContext: a wrong auto-name; 464 B): 32 Unk4 entries.
    struct Unk3 {
        void setPointer(void* const& ptr);

        Unk4 _0[32];
    };
    KSYS_CHECK_SIZE_NX150(Unk3, 0x2000);

    // Two-level free-list index. Bit N of mMask selects mMask2[N]; bit M of that word selects the
    // circular block list at mLists._0[N]._0[M]. 12B5900 processes the lowest set bit of each.
    struct FreeListTree32 {
        u32 mMask;
        u32 mMask2[32];
        Unk3 mLists;
    };
    KSYS_CHECK_SIZE_NX150(FreeListTree32, 0x2088);

    // Same index with 27 first-level entries, used by the heap's largest size class.
    struct FreeListTree27 {
        u32 mMask;
        u32 mMask2[27];
        Unk1 mLists;
    };
    KSYS_CHECK_SIZE_NX150(FreeListTree27, 0x1b70);

    // Block record (stride 0x80, array at +0x5cb0). 12B8A78 / 12B78BC read the in-use byte at
    // +0x18, the used-byte state at +0x19, the data pointer at +0x30 and lock at +0x40.
    struct Block {
        u8 _0[0x18];
        bool mInUse;
        u8 mState;
        u8 _1a[0x16];
        void* mData;
        u8 _38[0x8];
        sead::CriticalSection mLock;
    };
    KSYS_CHECK_SIZE_NX150(Block, 0x80);

    // Complete 12B77A8 produces this record; 12B78BC releases it.
    // The tagged heap word is opaque until its native helpers are established.
    struct Allocation {
        // Header in front of the data block. The distance from the header to the data is stored as
        // a u16 right before the data; 12B8A78 / 12B78BC check the magic word then read the flag
        // byte at +0x1a, the block index at +0x1c and the state byte at +0x1d.
        struct Header {
            static constexpr u32 cMagic = 0xad000d1e;
            static constexpr u32 cFreeMagic = 0xd15ab1ed;
            u32 mMagic;
            // 0x71012b7448 moves this from the heap's free total to its used total on release.
            // It is also the distance to the next block of the contiguous block chain.
            s32 mSize;
            // Distance to the previous block (the blocks are contiguous in address order).
            s32 mPrevDistance;
            // Links of the circular free-block lists; the distance is relative to the address of
            // the field itself.
            s32 mListNext;
            s32 mListPrev;
            u32 _14;
            // The header sits one u16 distance before the data block it describes.
            static Header* get(void* data) {
                auto* bytes = static_cast<u8*>(data);
                return reinterpret_cast<Header*>(bytes - *reinterpret_cast<u16*>(bytes - 2));
            }
            // Next block of the heap's block chain; a zero distance terminates the chain.
            Header* getNextBlock() {
                const s32 distance = mSize;
                return distance == 0
                           ? nullptr
                           : reinterpret_cast<Header*>(intptr_t(distance) +
                                                       reinterpret_cast<uintptr_t>(this));
            }
            // Next block of the list this header is linked on.
            Header* getListNext() {
                const s32 distance = mListNext;
                return distance == 0
                           ? nullptr
                           : reinterpret_cast<Header*>(intptr_t(distance) +
                                                       reinterpret_cast<uintptr_t>(&mListNext));
            }
            u8 _18[2];
            u8 mInUse : 1;
            u8 mFlag : 1;
            u8 _1a : 6;
            u8 _1b;
            u8 mBlockIndex;
            u8 _1d[3];
        };
        KSYS_CHECK_SIZE_NX150(Header, 0x20);
        // Complete 12B8C7C clears tag bit 0 under the owning heap lock; declaration only.
        void sub_71012B8C7C();
        // Complete 12B8C10 sets tag bit 0 and returns true; declaration only.
        bool sub_71012B8C10();
        // 0x71012b8ce8 (placeholder name): sets or clears tag bit 1, under the heap lock when the
        // allocation has data.
        void sub_71012B8CE8(bool x);
        // 0x71012B8A78: updates the block record for this allocation while the heap lock is held.
        void sub_71012B8A78(bool x);
        void* mData;
        u32 _8;
        u64 mTaggedHeap;
        s32 mSize;
    };
    KSYS_CHECK_SIZE_NX150(Allocation, 0x20);
    // Bounds-checked block record lookup. The original has no out-of-line copy: the same sequence
    // (compare against _5ca8, then index the records) recurs in 12B8A78 and 12B78BC.
    Block* getBlock(s32 index) {
        if (u32(index) >= _5ca8)
            return nullptr;
        return &_5cb0[index];
    }
    void x_21(Allocation* allocation);
    // 0x71012b5900 (CSV CompactedHeap::x): checks the heap's block and free lists and compacts
    // the indexed free lists. The name is only read by the original's debug assertions.
    void x(const sead::SafeString& name, bool sync);
    void x_7(bool x);
    // 0x71012b69f8 (placeholder name): compacts the free list selected by the tree word.
    Allocation::Header* x_8(FreeListTree32* tree, Allocation::Header* list, bool x);
    // 0x71012b646c (placeholder name): releases one allocation whose header may be corrupt.
    void x_9(Allocation::Header* allocation);
    // Complete 12B7354 / 12B7448 and archive callers establish these raw helpers.
    // Bodies remain undecompiled because their tagged allocation headers are opaque.
    void* x_17(u32 size, s32 alignment, s32 mode, bool sync);
    void x_19(void* data, bool sync);

    // The result of the raw block allocator x_13 (two pointers returned in x0 / x1).
    struct BlockInfo {
        void* mBlock;
        void* mTagged;
    };
    BlockInfo x_13(u32 size, s32 alignment);
    void* x_16(void* block, u32 size, void* tagged, s32 alignment);
    bool x_20(Allocation* allocation, size_t size, s32 alignment);

    void destroy();
    void incrementCompactionCount();
    bool setBuffer(void* buffer, size_t size);
    bool compact();

    // The state (_5c90): 3 once the compaction is finished.
    s32 getState() const { return _5c90; }
    void x_2();
    void x_3();
    bool x_4();
    void x_5();

private:
    friend class ::DungeonPackMgr;
    // Complete FE2E28 reads the signed free-size field directly.
    friend class TextureHandleMgr;
    virtual ~CompactedHeap();

    u8 _8[0x8];
    FreeListTree32 mFreeListTree;   // 0x10
    FreeListTree32 mFreeListTree2;  // 0x2098
    FreeListTree27 mFreeListTree3;  // 0x4120
    s32 _5c90;
    sead::Atomic<s32> mCompactionCount;
    void* _5c98;
    // 8A5700 adds these sizes after widening each signed word.
    s32 _5ca0;
    u8 _5ca4[0x5ca8 - 0x5ca4];
    // Number of block records; _5cb8 is the number the allocation walk scans.
    u32 _5ca8;
    Block* _5cb0;
    u32 _5cb8;
    u8 _5cbc[0x5ce0 - 0x5cbc];
    void* _5ce0;
    u8* _5ce8;
    u8* _5cf0;
    sead::CriticalSection _5cf8;
    sead::CriticalSection _5d38;
    sead::CriticalSection _5d78;
    u32 _5db8;
    // FE2E28 sign-extends this; complete 12B7448 adds each released block size.
    s32 _5dbc;
    sead::SafeString _5dc0;
};
KSYS_CHECK_SIZE_NX150(CompactedHeap, 0x5dd0);

}  // namespace ksys::res
