#pragma once

#include <cmath>
#include <limits>
#include <math/seadMathCalcCommon.h>

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
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResDerived.h"
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

namespace ksys::xlink {
class XLink;
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

// Placeholder name: one of the four regions of ClusteredRendererCells (sub_7101244210 resets and
// unloads the ones it no longer needs).
struct ClusteredRendererRegion {
    // Placeholder names: element types of the buffers below (layouts from sub_7101244980 / sub_710124474C).
    struct Sub {
        u8 _0[0x30];
        u8* _30;
        sead::Buffer<u8[0x44]> _38;
    };
    struct ModelEntry {
        u8 _0[0x8];
        xlink::XLink* mXLink;
        u8 _10[0x38 - 0x10];
    };
    struct ResEntry {
        void* _0;
        res::ResDerived mHandle;
    };
    struct TextureEntry {
        res::TextureHandleList::Entry mEntry;
        u8 _b0[0xc0 - 0xb0];
    };

    sead::Buffer<Sub*> mSubs;
    sead::Buffer<ModelEntry> mModels;
    sead::Buffer<ResEntry> mResources;
    sead::Buffer<u8> _30;
    sead::Buffer<u8> _40;
    sead::Buffer<TextureEntry> mTextures;
    sead::Heap* mHeap;
    // 2 and 3 are loading states (sub_7101244210 drops pending list items unless both tests pass).
    sead::Atomic<s32> mState;
    u8 _6c[0x7c - 0x6c];
    s32 _7c;
    u8 _80[0x88 - 0x80];
    u8* _88;
    sead::Atomic<u32> _90;
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
        ClusteredRendererRegion* mRegion;
        res::Handle* mHandle;
        u32 mFrame;
        u32 _14;
    };
    sead::ObjList<ListItem> _168;
    sead::CriticalSection _198;
    sead::CriticalSection _1d8;
    sead::CriticalSection _218;
    // Placeholder: a ring of 32 list items; 0x7101246fbc reads with atomic read counters.
    struct Queue {
        // inline-only in the original; name is a guess. sub_71012443AC and the thread function
        // 0x7101246fbc (twice) repeat it: drops entries whose region moved on (frame mismatch), then
        // appends `item` unless the write slot is still in use.
        bool push(const ListItem& item) {
            while (mRead != mWrite) {
                auto& entry = mItems[mRead % 32];
                if (entry.mFrame == entry.mRegion->_90)
                    break;
                entry.mRegion = nullptr;
                mRead.increment();
            }
            auto& slot = mItems[mWrite % 32];
            if (slot.mRegion)
                return false;
            slot = item;
            mWrite.increment();
            return true;
        }

        ListItem mItems[32];
        sead::Atomic<u32> mRead;
        sead::Atomic<u32> mWrite;
    };
    // startThread compares the counters (sends a message to the thread when a queue is not empty).
    Queue mQueues[3];
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
    // 0x7101246fbc (placeholder name): one step of the loader thread: moves regions from queue 0 to 1 (after
    // releasing their old data), loads queue 1 entries (loadX_0) into queue 2 and finishes queue 2.
    void sub_7101246FBC();
    // 0x710124474c (declaration only; placeholder name): releases a region's models and xlinks.
    void sub_710124474C(ClusteredRendererRegion* region);
    // 0x7101244980 (placeholder name): releases everything a region loaded; `unload` skips the
    // resetUnitFlag20000IfSuccess step.
    void sub_7101244980(ClusteredRendererRegion* region, bool unload);
    // 0x710124536c (CSV ClusteredRenderer::loadX_0; declaration only): 0 when the region must be finished in
    // queue 2.
    s32 loadX_0(ClusteredRendererRegion* region, res::Handle* handle, u32 frame);
    // 0x71012460a4 (declaration only; placeholder name): 1 = done, 2 = wait (sleep 33 ms).
    s32 sub_71012460A4(ClusteredRendererRegion* region, u32 frame);
    // 0x7101242720 (placeholder name): delegate _c48.
    void sub_7101242720(res::TextureHandleList::Entry* entry);

    // 0x71012439bc (placeholder name): stops the thread and releases everything init set up.
    void sub_71012439BC();
    // 0x7101243ea8 (placeholder name): finalizes and deletes `renderer`, then destroys its heap.
    static void sub_7101243EA8(ClusteredRenderer* renderer);
    // 0x7101244210 (placeholder name): moves to grid cell (x, z) (stored in _e8 / _ec): unloads the
    // regions sub_7101244C58 does not keep and loads the others.
    void sub_7101244210(s32 x, s32 z);
    // 0x7101244c58 (declaration only; placeholder name): bit i set = region i stays loaded for (x, z) (returned in a 64-bit register).
    u64 sub_7101244C58(s32 x, s32 z);
    // 0x7101244ea8 (CSV ClusteredRenderer::loadX; declaration only)
    void loadX(ClusteredRendererCells* cells, s32 region);
    // 0x71012443ac (placeholder name): finishes loading regions and queues the ones that are ready.
    void sub_71012443AC();
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
    // 0x7101244038 (placeholder name): per-frame update with the camera position: switches the grid cell
    // (500 m cells, 19 x 15) when it changed, queues finished loads and wakes the loader thread.
    void sub_7101244038(const sead::Vector3f* pos);

    // inline-only in the original; name is a guess. sub_7101244038 (x, y, z) and postCalcWorld 0x71012481f8
    // repeat it: not NaN, finite and within the s32 range.
    static bool isValidCoord(f32 value) {
        return !std::isnan(value) && !(sead::Mathf::abs(value) > std::numeric_limits<f32>::max()) &&
               !(sead::Mathf::abs(value) > 2147483648.0f);
    }
    // 0x7101243b70 (declaration only; placeholder name)
    void sub_7101243B70();
    // 0x71012497f8: calls `callback` for every cluster entry within `radius` of `pos`.
    void sub_71012497F8(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<map::Unk_71012497f8Entry*, bool>* callback);

    ClusteredRendererData mData;
    ClusteredRendererData2 mData2;
};

// Placeholder name: the object at ClusteredRenderer+0xf0: four regions with their resource handles and a
// buffer of cells at 0x60.
struct ClusteredRendererCells {
    u8 _0[0x20];
    ClusteredRendererRegion* mRegions[4];
    res::Handle* mHandles[4];
    sead::Buffer<ClusteredRenderer::Cell> mCells;
};

}  // namespace ksys::act
