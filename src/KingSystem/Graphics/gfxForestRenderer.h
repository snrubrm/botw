#pragma once

#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>

namespace ksys::map {
class PlacementMgr;
}

namespace ksys::gfx {

// TODO: incomplete
class ForestRenderer : public sead::hostio::Node {
public:
    // Placeholder names: the 0x88-byte entries of the buffer at 0xd0 and their 0x98-byte items.
    struct Item {
        u8 _0[0xc];
        sead::BitFlag16 _c;
        u8 _e[0x98 - 0xe];
    };
    static_assert(sizeof(Item) == 0x98);
    struct Entry {
        // 0x7100f0663c (declaration only; placeholder name): index of the item at `pos`, or -1.
        s32 sub_7100F0663C(const sead::Vector3f& pos);

        u8 _0[0x60];
        sead::Buffer<Item> mItems;
        u8 _70[0x88 - 0x70];
    };
    static_assert(sizeof(Entry) == 0x88);

    // 0x7100f03b68 (placeholder name): sets bit 1 of every item's flags.
    void sub_7100F03B68();

    virtual ~ForestRenderer();

    s32 x_7(const sead::Vector3f& vec);
    // 0x7100f06798 (CSV x_8; declaration only)
    void x_8(s32 idx, bool a, bool b);
    // 0x7100f03c18 (declaration only; placeholder name)
    void sub_710F03C18(const sead::Vector3f* pos);
    // 0x7100f06904 (declaration only; placeholder name)
    void sub_710F06904(map::PlacementMgr* mgr, bool a);
    bool x_9();
    // 0x7100f03af0 (CSV ForestRenderer::stopped): true unless the renderer has reached state 5 with _220 set in
    // a non-debug, non-dungeon stage (or the final trial); in state 6 it is true if bit 0 of _50 is set and
    // _60 > 3.
    bool stopped();

    sead::CriticalSection mCS;
    u64 _48;
    u32 _50;
    s32 _54;
    u8 _58[0x60 - 0x58];
    s32 _60;
    u8 _64[0xd0 - 0x64];
    sead::Buffer<Entry> mEntries;
    u8 _e0[0x220 - 0xe0];
    u32 _220;
};

}  // namespace ksys::gfx
