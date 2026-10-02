#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

namespace ksys::phys {

// InstanceSet::mClothSet (no name known in the CSV). TODO: incomplete (size unknown).
class ClothSet {
public:
    // Placeholder: 0x40-byte cloth entry.
    struct Unk1 {
        /* 0x00 */ u8 _0[0x18];
        /* 0x18 */ u32 _18;  // flags (bit 3 is set by the DisableCloth behavior)
        /* 0x1c */ u8 _1c[0x40 - 0x1c];
    };

    /* 0x00 */ u8 _0[0x18];
    /* 0x18 */ sead::Buffer<Unk1> _18;
};

}  // namespace ksys::phys
