#pragma once

#include <container/seadListImpl.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::tera {

// Placeholder (ctor 0x710110cfd0, init 0x710110d034; size 0x28). Created for each
// Unk_7101108460 node. Bit 0 / bit 3 of _8 are flags read and set by the resource managers.
class Unk_710110cfd0 {
public:
    u8 _0[0x8];
    u32 _8;
    u8 _c[0x28 - 0xc];
};

// Placeholder (ctor 0x710110d278, init 0x710110d2c4; size 0xa8). _8 points to the key the managers
// search by (first u16 is its id); _a0 is compared with epsilon by 0x7101108624.
class Unk_710110d278 {
public:
    struct Key {
        u16 id;
    };

    u8 _0[0x8];
    Key* _8;
    u8 _10[0xa0 - 0x10];
    f32 _a0;
    u8 _a4[0xa8 - 0xa4];
};

// Placeholder name (inline ctor in the factory 0x7101108460; size 0x30): a list node that is its own
// list data; the factory links it into the list at +0x88 of its owner.
class Unk_7101108460 : public sead::ListNode {
public:
    // 0x7101107e90
    Unk_710110cfd0* getA();
    // 0x710110860c
    const Unk_710110cfd0* getA() const;
    // 0x7101107760
    Unk_710110d278* getB() const;
    // 0x7101108614 (placeholder name): id of the key of B.
    u16 sub_7101108614() const;
    // 0x7101108624 (placeholder name): B's _a0 is above epsilon.
    bool sub_7101108624() const;

    Unk_7101108460* mData;
    void* mList;
    Unk_710110cfd0* mA;
    Unk_710110d278* mB;
};

}  // namespace ksys::tera

namespace ksys::tera {

// Placeholder (callers 0x7101108ae8, 0x7101109bd8, 0x710110a468, 0x710110a740, 0x7101105b2c,
// 0x7100f289f0): an array of 0x528-byte areas at _8 with a base size at _18 and a level in the top
// three bits of _1e.
struct Unk_71010FEDBC {
    struct Area {
        sead::Vector2f center;
        u8 _8[0x18 - 0x8];
        f32 size;
        u8 _1c[0x528 - 0x1c];
    };

    // 0x71010fedbc (placeholder name): the last of the first `count` areas whose distance from `pos`
    // (plus `margin`) is in range of the current level, or -1.
    s32 sub_71010FEDBC(const sead::Vector2f& pos, u32 count, f32 margin) const;

    // Placeholder: what sub_71010FE920 writes for an area.
    struct Result {
        sead::Vector2f pos;
        void* _8;
        s32 _10;
        u8 _14;
        u8 _15;
        bool _16;
    };
    // 0x71010fe920 (declared only; 624 B): fills `result` for area `index` and `pos`.
    bool sub_71010FE920(Result* result, const sead::Vector2f& pos, s32 index) const;

    u8 _0[0x8];
    Area* mAreas;
    u8 _10[0x18 - 0x10];
    f32 _18;
    u8 _1c[0x1e - 0x1c];
    s8 _1e;
};

// Placeholder: the flags 0x7101108ae8 reads (both low bits of _0 must be set; _2 is a level limit).
struct Unk_7101108AE8Flags {
    u8 _0;
    u8 _1;
    u8 _2;
};

// 0x7101108ae8 (placeholder name): searches the areas from the highest usable level down for one
// whose position for `pos` is in [-1, 2); returns 2 (or 1 if its _10 is set) and writes the position
// and area index, or returns 0.
u32 sub_7101108AE8(sead::Vector2f* out_pos, s32* out_index, const sead::Vector2f& pos,
                   const Unk_7101108AE8Flags& flags, const Unk_71010FEDBC& areas, u32 max_level);

}  // namespace ksys::tera
