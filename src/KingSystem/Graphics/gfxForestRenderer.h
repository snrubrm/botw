#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace gsys {
class Model;
class ModelUnit;
}  // namespace gsys

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

        u8 _0[0xc];
        sead::BitFlag16 _c;
        u8 _e[0x98 - 0xe];
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

        u8 _0[0x18];
        sead::Buffer<Record> mRecords;
        u8 _28[0x60 - 0x28];
        sead::Buffer<Item> mItems;
        u8 _70[0x88 - 0x70];
    };
    static_assert(sizeof(Entry) == 0x88);
    // Placeholder: the 0x60-byte entries of the buffer at 0xe8. requestDraw hands the draw array of
    // mModelUnit one of two blocks of 0x400 unit pointers (mUnits[mIndex * 0x400], mCount used) when
    // mState is 3, then flips mIndex.
    struct UnitEntry {
        u8 _0[0x8];
        s32 mState;
        u8 _c[0x20 - 0xc];
        void** mUnits;
        u32 mIndex;
        u32 mCount;
        u32 mPrevCount;
        u8 _34[0x38 - 0x34];
        gsys::ModelUnit* mModelUnit;
        u8 _40[0x60 - 0x40];
    };
    static_assert(sizeof(UnitEntry) == 0x60);

    // 0x7100f06474 (CSV name): clears bit 2 of every record and sets bit 1 of every item.
    void x_1();
    // 0x7100f03b68 (placeholder name): sets bit 1 of every item's flags.
    void sub_7100F03B68();

    virtual ~ForestRenderer();

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

    // Placeholder: the two 0x50-byte model slots at 0x110; requestDraw draws the slot 1 - _1b0 when its
    // state is 2.
    struct ModelSlot {
        u8 _0[0x8];
        gsys::Model* mModel;
        u8 _10[0x48 - 0x10];
        s32 mState;
        u8 _4c[0x50 - 0x4c];
    };
    static_assert(sizeof(ModelSlot) == 0x50);

    sead::CriticalSection mCS;
    u64 _48;
    u32 _50;
    s32 _54;
    u8 _58[0x60 - 0x58];
    s32 _60;
    u8 _64[0xd0 - 0x64];
    sead::Buffer<Entry> mEntries;
    u8 _e0[0xe8 - 0xe0];
    sead::Buffer<UnitEntry> mUnitEntries;
    u8 _f8[0x110 - 0xf8];
    sead::SafeArray<ModelSlot, 2> mModelSlots;
    s32 _1b0;
    u8 _1b4[0x220 - 0x1b4];
    u32 _220;
};

}  // namespace ksys::gfx
