#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <cstddef>
#include <Havok/Common/Base/Container/String/hkStringPtr.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>

namespace ksys::phys {

// InstanceSet::mClothSet (no name known in the CSV). TODO: incomplete (size unknown).
class ClothSet {
public:
    // Placeholder chain down to the Havok cloth particle array (types not in hkStubs).
    struct ParticleUnk {
        u8 _0[0x8];
        f32 _8;  // written by sub_710121C26C
        u8 _c[0x10 - 0xc];
    };
    struct ClothDataUnk {
        u8 _0[0x38];
        ParticleUnk* mParticles;
        s32 mNumParticles;
    };
    struct ClothUnk3 {
        u8 _0[0x10];
        ClothDataUnk* _10;
    };
    struct ClothUnk2 {
        ClothUnk3* _0;
    };
    // Placeholder: the object holding the cloth's name (a Havok string pointer).
    struct ClothUnk4 {
        u8 _0[0x10];
        hkStringPtr mName;
    };
    struct ClothUnk1 {
        u8 _0[0x10];
        ClothUnk4* _10;
        u8 _18[0x20 - 0x18];
        ClothUnk2* _20;
    };

    // Placeholder: 0x20-byte element of Unk1::_8; sub_7101218A90 passes `_8` to the hkArray release 0x7101409fc8.
    struct Unk2 {
        /* 0x00 */ u8 _0[0x8];
        /* 0x08 */ void* _8;
        /* 0x10 */ u8 _10[0x20 - 0x10];
    };

    // Placeholder: 0x40-byte cloth entry.
    struct Unk1 {
        /* 0x00 */ ClothUnk1* _0;
        /* 0x08 */ sead::Buffer<Unk2> _8;
        /* 0x18 */ u32 _18;  // flags (bit 3 is set by the DisableCloth behavior)
        /* 0x1c */ u8 _1c[0x30 - 0x1c];
        /* 0x30 */ u32 _30;
        /* 0x34 */ u8 _34[0x3c - 0x34];
        /* 0x3c */ f32 _3c;  // set to 1.0 by SiteBossReaction::leave_
    };

    // 0x7101218a90: called by GelEnemy::m79: clears _30 and bit 1 of every entry, sets bit 2, releases every
    // entry's hkArray through 0x7101409fc8, then clears the 8 bytes at 0x5c.
    void sub_7101218A90();
    // 0x7101218bcc (unnamed in the CSV): enables (bit 0x2000 of _70) or, while _60 >= 1, disables every entry
    // through 0x7101218c70.
    void sub_7101218BCC(bool enabled);
    // 0x7101218c70 (unnamed; declared only): updates entry `index` with the cloth `enabled` flag.
    void sub_7101218C70(s32 index, bool enabled);
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
    /* 0x28 */ u8 _28[0x5c - 0x28];
    /* 0x5c */ u32 _5c;
    /* 0x60 */ f32 _60;  // read by ForkClothOnOffASPlay::enter_ (cloth is off while < 1)
    /* 0x64 */ sead::Vector3f _64;  // wind (set by InstanceSet::sub_7100FBD410)
    /* 0x70 */ u32 _70;  // flags (bit 16 is set by SunazarashiRoot::init_; bit 15 by InstanceSet::sub_7100FBD3EC)
};
static_assert(offsetof(ClothSet, _70) == 0x70);

// 0x7101409fc8 (declared only; unnamed): releases the hkArray at `array` (count +0x18, data +0x10) and fills it
// with the freed pattern; called for every element of ClothSet::Unk1::_8.
void sub_1409FC8(void* array);

}  // namespace ksys::phys
