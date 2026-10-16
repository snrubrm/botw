#pragma once

#include <container/seadListImpl.h>
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
