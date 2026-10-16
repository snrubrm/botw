#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadBitFlag.h>
#include <container/seadBuffer.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadMessageQueue.h>

namespace sead {
class DelegateThread;
class Heap;
class Thread;
}  // namespace sead

namespace gsys {
class Model;
}

namespace ksys::map {
struct Unk_71012497f8Entry;
}

namespace ksys::act {

// TODO
class ClusteredRenderer {
public:
    // Placeholder names: the objects that cell entries point to (layouts unknown).
    struct Unk_CellNode;
    struct Unk_CellNode2;

    // Placeholder name: a fixed ring of pointers; push writes at the write counter modulo N.
    template <typename T, s32 N>
    struct PtrQueue {
        void push(T* item) { mItems[mWrite++ % N] = item; }

        T* mItems[N];
        u32 mRead;
        u32 mWrite;
    };

    // Placeholder names: one 9 x 9 grid of entries; the object at 0xf0 holds a buffer of these at 0x60.
    struct Cell {
        struct Entry {
            u64 _0;
            u64 _8;
            sead::Vector2i _10;
            s64 _18;
            Unk_CellNode* _20;
            Unk_CellNode2* _28[3];
        };
        static_assert(sizeof(Entry) == 0x40);

        // 0x710124749c (declaration only; placeholder name): drains the queues below.
        void sub_710124749C(void** freeList, void* unk);

        Entry mEntries[9][9];
        u8 _1440[0x1454 - 0x1440];
        s32 _1454;
        PtrQueue<Unk_CellNode, 81> _1458;
        PtrQueue<Unk_CellNode2, 243> _16e8[2];
    };
    static_assert(sizeof(Cell) == 0x2628);
    struct Unk_f0 {
        u8 _0[0x60];
        sead::Buffer<Cell> mCells;
    };

    // 0x7101243bd8 (placeholder name): resets every cell and releases the heap at 0xbf0 (destroys it when
    // flag bit 17 is set, else frees all of it) if flag bit 18 is set.
    void sub_7101243BD8(bool release);
    // 0x7101243eec (placeholder name): resets the entries of a cell.
    void sub_7101243EEC(Cell* cell);

    void startThread();
    void requestDraw();
    // 0x7101244598 (declaration only; placeholder name)
    void sub_7101244598();
    // 0x710124929c (declaration only; placeholder name; the same arguments as sub_71012497F8)
    void sub_710124929C(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<map::Unk_71012497f8Entry*, bool>* callback);
    // 0x7101244038 (declaration only; placeholder name)
    void sub_7101244038(const sead::Vector3f* pos);
    // 0x7101243b70 (declaration only; placeholder name)
    void sub_7101243B70();
    // 0x71012497f8: calls `callback` for every cluster entry within `radius` of `pos`.
    void sub_71012497F8(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<map::Unk_71012497f8Entry*, bool>* callback);

    // 2026-10-07: requestDraw at 0x7101247448 reads this model and these counters.
    u8 _0[0xf0];
    Unk_f0* _f0;
    u8 _f8[0x108 - 0xf8];
    gsys::Model* _108;
    u8 _110[0x198 - 0x110];
    sead::CriticalSection _198;
    sead::CriticalSection _1d8;
    sead::CriticalSection _218;
    u8 _258[0x558 - 0x258];
    // startThread compares these three pairs (sends a message to the thread when one differs).
    s32 _558;
    s32 _55c;
    u8 _560[0x860 - 0x560];
    s32 _860;
    s32 _864;
    u8 _868[0xb68 - 0x868];
    s32 _b68;
    s32 _b6c;
    u8 _b70[0xba8 - 0xb70];
    void* _ba8;
    u8 _bb0[0xbb8 - 0xbb0];
    u8 _bb8[0xbf0 - 0xbb8];
    sead::Heap* _bf0;
    u8 _bf8[0xc00 - 0xbf8];
    sead::Delegate2<ClusteredRenderer, sead::Thread*, sead::MessageQueue::Element> mThreadDelegate;
    s32 mThreadPriority;
    sead::Heap* mHeap;
    sead::DelegateThread* mThread;
    u32 _c38;
    u32 _c3c;
    u8 _c40[4];
    s32 _c44;
    u8 _c48[0xc9c - 0xc48];
    u32 _c9c;
};

}  // namespace ksys::act
