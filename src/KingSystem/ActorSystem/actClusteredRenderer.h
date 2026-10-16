#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadBitFlag.h>
#include <container/seadBuffer.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadAtomic.h>
#include <thread/seadMessageQueue.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglGPUMemBlock.h>
#include <container/seadFreeList.h>
#include <container/seadObjList.h>
#include <gsys/gsysIModelProcedural.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resTextureHandleList.h"

namespace sead {
class DelegateThread;
class Heap;
class Thread;
}  // namespace sead

namespace gsys {
class Model;
class ModelScene;
class ModelViewData;
}  // namespace gsys


namespace ksys::map {
struct Unk_71012497f8Entry;
}

namespace ksys::act {

class ClusteredRenderer;
struct ClusteredRendererCells;

// Placeholder names: what TextureHandleList::Entry::sub_71012BD4D8 returns, as used by
// ClusteredRenderer::sub_7101242720 (a use count at 0x84 of the owner and a bit per slot index).
struct ClusteredRendererTexOwnerMaybe {
    u8 _0[0x84];
    s32 mUseCount;
    struct UsedBits {
        u32 _0;
        u32 mWords[1];
    };
    UsedBits* mUsedBits;
};
struct ClusteredRendererTexMaybe {
    u8 _0[0xb0];
    ClusteredRendererTexOwnerMaybe* mOwner;
    u32 mIndex;
};

// Placeholder: the second base of ClusteredRenderer (at 0xe0; its vtable 0x7102516df0 in ClusteredRenderer's
// vtable group has only the destructor thunks 0x71012427dc / 0x71012428c4).
class Unk_7102516df0 {
public:
    virtual ~Unk_7102516df0() = default;
};

// Placeholder name: ClusteredRenderer's data (0xe8 - 0xc68). The ctor 0x71012424e4 value-initialises it
// (memset 0xe8 - 0xc68 after the vtable stores), and the destructor
// 0x7101242774 destroys its members after storing both ClusteredRenderer vtables. A member: the
// ctor stores the ClusteredRenderer vtables before the memset.
struct ClusteredRendererData {
    s32 _e8;
    s32 _ec;
    ClusteredRendererCells* _f0;
    sead::Heap* _f8;
    u8 _100[0x108 - 0x100];
    gsys::Model* _108;
    sead::FixedSafeString<64> _110;
    // Placeholder item type (0x18 bytes; the list node follows at 0x18).
    struct ListItem {
        u8 _0[0x18];
    };
    sead::ObjList<ListItem> _168;
    sead::CriticalSection _198;
    sead::CriticalSection _1d8;
    sead::CriticalSection _218;
    // Three rings of 32 entries of 0x18 bytes (read by 0x7101246fbc with atomic read counters).
    u8 _258[0x558 - 0x258];
    // startThread compares these three pairs (sends a message to the thread when one differs).
    sead::Atomic<s32> _558;
    sead::Atomic<s32> _55c;
    u8 _560[0x860 - 0x560];
    sead::Atomic<s32> _860;
    sead::Atomic<s32> _864;
    u8 _868[0xb68 - 0x868];
    sead::Atomic<s32> _b68;
    sead::Atomic<s32> _b6c;
    agl::GPUMemBlock<u8> _b70;
    // Two free lists whose work buffers come from the heap at 0xf8.
    sead::FreeList _ba8;
    sead::FreeList _bb8;
    sead::Vector3f _bc8;
    agl::GPUMemAddrBase _bd8;
    sead::Heap* _bf0;
    u64 _bf8;
    sead::Delegate2<ClusteredRenderer, sead::Thread*, sead::MessageQueue::Element> mThreadDelegate;
    s32 mThreadPriority;
    sead::Heap* mHeap;
    sead::DelegateThread* mThread;
    u32 _c38;
    u32 _c3c;
    u32 _c40;
    s32 _c44;
    sead::AnyDelegate1<res::TextureHandleList::Entry*> _c48;
};

// Placeholder name: ClusteredRenderer's data at 0xc68 - 0xca0, value-initialised separately by the ctor
// (zero stores to 0xc68 - 0xca0 after the memset of ClusteredRendererData, then the values below).
struct ClusteredRendererData2 {
    u32 _c68;
    u32 _c6c;
    s32 _c70;
    f32 _c74;
    u64 _c78;
    u64 _c80;
    u64 _c88;
    u64 _c90;
    u32 _c98;
    u32 _c9c;
};

// vtable 0x7102516b30 (84 slots). getName returns "ClusteredRenderer".
class ClusteredRenderer : public gsys::IModelProcedural, public Unk_7102516df0 {
    SEAD_RTTI_OVERRIDE(ClusteredRenderer, gsys::IModelProcedural)
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
        void sub_710124749C(sead::FreeList* node_list, sead::FreeList* node2_list);

        Entry mEntries[9][9];
        u8 _1440[0x1454 - 0x1440];
        s32 _1454;
        PtrQueue<Unk_CellNode, 81> _1458;
        PtrQueue<Unk_CellNode2, 243> _16e8[2];
    };
    static_assert(sizeof(Cell) == 0x2628);
    ClusteredRenderer();
    ~ClusteredRenderer() override;
    sead::SafeString getName() const override;
    // 0x71012481f8 (declaration only)
    void postCalcWorld(const gsys::ModelScene* scene, u32, u32,
                       const gsys::ModelViewData* model_view_data, int) override;
    // 0x7101248af0 (declaration only; placeholder name and argument types): new virtual, slot 83.
    virtual void sub_7101248AF0(void* unused, const void* arg);

    // 0x7101249fc0 (placeholder name): tries to lock _218, _198 and _1d8; on failure unlocks the ones taken.
    bool sub_7101249FC0();
    // 0x710124a02c (placeholder name): unlocks _1d8, _198 and _218.
    void sub_710124A02C();
    // 0x710124271c (placeholder name): the thread function (mThreadDelegate).
    void sub_710124271C(sead::Thread* thread, sead::MessageQueue::Element msg);
    // 0x7101246fbc (declaration only; placeholder name)
    void sub_7101246FBC();
    // 0x7101242720 (placeholder name): delegate _c48.
    void sub_7101242720(res::TextureHandleList::Entry* entry);

    // 0x71012439bc (placeholder name): stops the thread and releases everything init set up.
    void sub_71012439BC();
    // 0x7101243ea8 (placeholder name): finalizes and deletes `renderer`, then destroys its heap.
    static void sub_7101243EA8(ClusteredRenderer* renderer);
    // 0x7101243cd8 (declaration only; placeholder name): releases the cell object.
    void sub_7101243CD8(ClusteredRendererCells* cells);

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

    ClusteredRendererData mData;
    ClusteredRendererData2 mData2;
};

// Placeholder name: the object at ClusteredRenderer+0xf0 holds a buffer of cells at 0x60.
struct ClusteredRendererCells {
    u8 _0[0x60];
    sead::Buffer<ClusteredRenderer::Cell> mCells;
};

}  // namespace ksys::act
