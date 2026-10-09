#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <cstddef>
#include <container/seadBuffer.h>
#include <math/seadVector.h>

namespace ksys::phys {

// InstanceSet::mClothSet (no name known in the CSV). TODO: incomplete (size unknown).
class ClothSet {
public:
    // Placeholder: 0x40-byte cloth entry.
    struct Unk1 {
        /* 0x00 */ u8 _0[0x18];
        /* 0x18 */ u32 _18;  // flags (bit 3 is set by the DisableCloth behavior)
        /* 0x1c */ u8 _1c[0x3c - 0x1c];
        /* 0x3c */ f32 _3c;  // set to 1.0 by SiteBossReaction::leave_
    };

    // 0x7101218a90 (declared only): called by GelEnemy::m79.
    void sub_7101218A90();
    // Full12193C4 and independent ForestGiant706818: signed cloth index, -1 when absent.
    s32 sub_71012193C4(const sead::SafeString& name);
    // Full121C26C bounds-checks both signed indices and stores value at the selected item+8.
    void sub_710121C26C(s32 cloth_index, s32 item_index, f32 value);
    // 0x71012189b8: updates each cloth entry's enabled flags.
    void sub_71012189B8(bool enabled);

    /* 0x00 */ u8 _0[0x8];
    /* 0x08 */ void* _8;  // tested by ClothStiffnessMgr::sub_7100665A84
    /* 0x10 */ u8 _10[0x18 - 0x10];
    /* 0x18 */ sead::Buffer<Unk1> _18;
    /* 0x28 */ u8 _28[0x60 - 0x28];
    /* 0x60 */ f32 _60;  // read by ForkClothOnOffASPlay::enter_ (cloth is off while < 1)
    /* 0x64 */ sead::Vector3f _64;  // wind (set by InstanceSet::sub_7100FBD410)
    /* 0x70 */ u32 _70;  // flags (bit 16 is set by SunazarashiRoot::init_; bit 15 by InstanceSet::sub_7100FBD3EC)
};
static_assert(offsetof(ClothSet, _70) == 0x70);

}  // namespace ksys::phys
