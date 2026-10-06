#pragma once

#include <basis/seadTypes.h>
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

    /* 0x00 */ u8 _0[0x18];
    /* 0x18 */ sead::Buffer<Unk1> _18;
    /* 0x28 */ u8 _28[0x60 - 0x28];
    /* 0x60 */ f32 _60;  // read by ForkClothOnOffASPlay::enter_ (cloth is off while < 1)
    /* 0x64 */ sead::Vector3f _64;  // wind (set by InstanceSet::sub_7100FBD410)
    /* 0x70 */ u32 _70;  // flags (bit 16 is set by SunazarashiRoot::init_; bit 15 by InstanceSet::sub_7100FBD3EC)
};
static_assert(offsetof(ClothSet, _70) == 0x70);

}  // namespace ksys::phys
