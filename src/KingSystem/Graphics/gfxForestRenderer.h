#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <gsys/gsysModel.h>
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"

namespace gsys {
class Model;
class ModelUnit;
}  // namespace gsys

namespace ksys {
class TaskPostRunResult;
class TaskPostRunContext;
}  // namespace ksys

namespace ksys::map {
class PlacementMgr;
}

namespace ksys::gfx {

// TODO: incomplete
class ForestRenderer : public sead::hostio::Node {
public:
    // Placeholder names: the 0x88-byte entries of the buffer at 0xd0 and their 0x98-byte items.
    struct Item {
        // 0x7100f0914c (declared only; placeholder name): updates the item for the changed record; true stops
        // ForestRenderer::x_8's loop.
        bool sub_7100F0914C(void* record, bool a, bool b);

        // 0x7100f078a4 (vtable 0x71024f38b8): releases the item's pointer array and resets it if _8 is set.
        virtual ~Item();

        u32 _8;
        sead::BitFlag16 _c;
        u8 _e[0x10 - 0xe];
        u32 _10;
        u64 _18;
        sead::PtrArray<u8> _20;
        u64 _30;
        u16 _38;
        u8 _3a;
        u8 _3b;
        u8 _3c;
        u8 _3d;
        u8 _3e[0x40 - 0x3e];
        u64 _40;
        u8 _48[0x98 - 0x48];
    };
    static_assert(sizeof(Item) == 0x98);
    struct Entry {
        // 0x7100f0663c (declaration only; placeholder name): index of the item at `pos`, or -1.
        s32 sub_7100F0663C(const sead::Vector3f& pos);
        // 0x7100f071c4 (declaration only; placeholder name): adds a tree instance (name, position, rotation in
        // degrees, scale) if the entry handles that model.
        bool sub_7100F071C4(const sead::SafeString& name, const sead::Vector3f& pos,
                            const sead::Vector3f& rotate, f32 scale);

        // Placeholder: the 0x1c-byte records of the buffer at 0x18.
        struct Record {
            u8 _0[4];
            sead::BitFlag8 _4;
            u8 _5[0x1c - 0x5];
        };

        // 0x7100f07060 (placeholder name): allocates and clears the record buffer (_70 records) and the
        // u16 table (80 entries if bit 0 of _8 is set, else 1280).
        void sub_7100F07060();

        u8 _0[0x8];
        u32 _8;
        u8 _c[0x10 - 0xc];
        sead::Heap* mHeap;
        sead::Buffer<Record> mRecords;
        u8 _28[0x60 - 0x28];
        sead::Buffer<Item> mItems;
        s32 mNumRecords;
        u8 _74[0x78 - 0x74];
        sead::Buffer<u16> _78;
    };
    static_assert(sizeof(Entry) == 0x88);
    // Placeholder: the 0x60-byte entries of the buffer at 0xe8. requestDraw hands the draw array of
    // mModelUnit one of two blocks of 0x400 unit pointers (mUnits[mIndex * 0x400], mCount used) when
    // mState is 3, then flips mIndex.
    // vtable 0x71024f38d8.
    struct UnitEntry {
        // 0x7100f09374: deletes the model unit, resets the fields and frees the unit buffer.
        virtual ~UnitEntry();

        s32 mState;
        u8 _c[0x18 - 0xc];
        // Two blocks of 0x400 unit pointers (requestDraw reads the buffer through data()).
        sead::PtrArrayImpl mUnits;
        u32 mIndex;
        u32 mCount;
        u32 mPrevCount;
        u8 _34[0x38 - 0x34];
        gsys::ModelUnit* mModelUnit;
        u64 _40;
        s32 _48;
        s32 _4c;
        u64 _50;
        u8 _58[0x60 - 0x58];
    };
    static_assert(sizeof(UnitEntry) == 0x60);

    // Placeholder name (vtable 0x71024f38f8): the holder of the unit entries at 0xe0.
    struct UnitEntryBuffer {
        // 0x7100f0942c: frees the entry buffer.
        virtual ~UnitEntryBuffer();

        sead::Buffer<UnitEntry> mEntries;
    };

    // 0x7100f06474 (CSV name): clears bit 2 of every record and sets bit 1 of every item.
    void x_1();
    // 0x7100f03b68 (placeholder name): sets bit 1 of every item's flags.
    void sub_7100F03B68();

    // 0x7100f01acc
    ForestRenderer();
    virtual ~ForestRenderer();

    // 0x7100f01bf8 / 0x7100f01ef8 (CSV names; declaration only): targets of the delegates at 0x1e0 / 0x200.
    bool invoked2(void* arg);
    bool invoked3(void* arg);

    s32 x_7(const sead::Vector3f& vec);
    // 0x7100f06798 (CSV x_8): `idx` from x_7 (entry << 16 | record). With `b` it clears record flags 1, 2 and 6;
    // otherwise it sets / clears flag 2 (`a` clears) and lets the entry's items react.
    void x_8(s32 idx, bool a, bool b);
    // 0x7100f03c18 (declaration only; placeholder name)
    void sub_710F03C18(const sead::Vector3f* pos);
    // 0x7100f06904 (placeholder name; the arguments are unused): flushes the UBOs of every unit's draw array.
    void sub_710F06904(map::PlacementMgr* mgr, bool a);
    bool x_9();
    // 0x7100f07150 (CSV x_6): passes a placed tree to every entry (PlacementMapMgr::initForestRendererFiles).
    bool x_6(const sead::SafeString& name, const sead::Vector3f& pos, const sead::Vector3f& rotate,
             f32 scale);
    // 0x7100f03af0 (CSV ForestRenderer::stopped): true unless the renderer has reached state 5 with _220 set in
    // a non-debug, non-dungeon stage (or the final trial); in state 6 it is true if bit 0 of _50 is set and
    // _60 > 3.
    bool stopped();
    // 0x7100f03964
    void requestDraw();
    // 0x7100f01ab4 / 0x7100f01ac0 (placeholder names): return the addresses of two file statics
    // (0x710260a1d8: requestDraw draws nothing while it is set; 0x710260a1dc).
    static bool* sub_7100F01AB4();
    static u32* sub_7100F01AC0();

    // Placeholder name (vtable 0x71024f38a8): one of the 25 tree model resources (buffer at 0xf8, filled by init
    // 0x7100f02dac with the names "Obj_TreeBroadleaf_A", ...).
    struct TreeResMaybe {
        // 0x7100f07828
        virtual ~TreeResMaybe();

        bool _8 = false;
        u8 mIndex = 0xff;
        const char* mName = nullptr;
        res::ResDerived mRes;
        u64 _68 = 0;
    };
    static_assert(sizeof(TreeResMaybe) == 0x70);

    // Placeholder name (vtable 0x71024f3918): the two 0x50-byte model slots at 0x110; requestDraw draws the
    // slot 1 - _1b0 when its state is 2.
    struct ModelSlot {
        // 0x7100f095b8
        virtual ~ModelSlot();

        // inline-only in the original; name is a guess. ~ModelSlot and ~ModelSet (for each slot, before the
        // slot destructors) repeat it.
        void finalize() {
            mRes.sub_7100FDD264();
            if (mModel) {
                gsys::Model::sub_7100BF69F8(mModel);
                mModel = nullptr;
            }
        }

        gsys::Model* mModel = nullptr;
        res::Unk_71024f9958 mRes;
        s32 mState = 0;
    };
    static_assert(sizeof(ModelSlot) == 0x50);

    // Placeholder name (vtable 0x71024f3938): the double-buffered model slots at 0x108; mCurrent (0x1b0) is
    // flipped by requestDraw.
    struct ModelSet {
        // 0x7100f09658
        virtual ~ModelSet();

        sead::SafeArray<ModelSlot, 2> mSlots;
        s32 mCurrent = 0;
    };

    // Placeholder name (vtable 0x71024f3978; D1 0x7100f09780 / D0 0x7100f09800): the locked object at 0x68.
    // Its destructor releases _50 and _58 under the lock when bit 0 of mFlags is set.
    struct Unk_68 {
        virtual ~Unk_68();

        sead::CriticalSection mCS;
        u32 mFlags = 0;
        void* _50 = nullptr;
        sead::PtrArrayImpl _58;
    };
    static_assert(sizeof(Unk_68) == 0x68);

    sead::CriticalSection mCS;
    u64 _48 = 0;
    u32 _50 = 0;
    s32 _54 = 0;
    u32 _58 = 0;
    s32 _5c = -1;
    s32 _60 = 0;
    Unk_68 _68;
    sead::Buffer<Entry> mEntries;
    UnitEntryBuffer mUnitEntries;
    sead::Buffer<TreeResMaybe> mTreeRes;
    ModelSet mModelSet;

    // Placeholder name: the object at 0x1b8, target of the post-run task delegate the ctor builds at 0x1c0.
    struct Unk_1b8 {
        // 0x7100f07818 (CSV ForestRenderer::invoked1): clears bit 0.
        void invoked1(TaskPostRunResult* result, const TaskPostRunContext& context);

        u32 mFlags = 0;
    };
    Unk_1b8 _1b8;
    sead::Delegate2<Unk_1b8, TaskPostRunResult*, const TaskPostRunContext&> mPostRunDelegate{
        &_1b8, &Unk_1b8::invoked1};
    sead::Delegate1R<ForestRenderer, void*, bool> mDelegate2{this, &ForestRenderer::invoked2};
    sead::Delegate1R<ForestRenderer, void*, bool> mDelegate3{this, &ForestRenderer::invoked3};
    u32 _220 = 0;
    u64 _228 = 0;
    u64 _230 = 0;
};
static_assert(sizeof(ForestRenderer) == 0x238);

}  // namespace ksys::gfx
