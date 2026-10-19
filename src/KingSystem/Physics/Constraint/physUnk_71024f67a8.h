#pragma once

#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

// Whole factory 0x7100f71be4 allocates 0x40 and installs the complete
// two-slot lifetime table 0x71024f67a8. The payload has no member destructor.
// The factory's argument is the 0x30-byte block the AI init code builds on the stack:
// a u64 at +0, two Vector3f at +8 / +0x14 and a Vector4f at +0x20.
class Unk_71024f67a8 {
public:
    struct InitArg {
        u64 _0;
        sead::Vector3f _8;
        sead::Vector3f _14;
        sead::Vector4f _20;
    };
    static_assert(sizeof(InitArg) == 0x30);

    Unk_71024f67a8() = default;
    virtual ~Unk_71024f67a8();

    // 0x7100f71be4: allocates the object and copies the argument over the default
    // basis (ey / ez) and unit w.
    static Unk_71024f67a8* create(const InitArg& arg, sead::Heap* heap);

    static void sub_7100F71CB4(Unk_71024f67a8* object);

private:
    /* 0x08 */ u64 _8 = 0;
    /* 0x10 */ sead::Vector3f _10 = sead::Vector3f::ey;
    /* 0x1c */ sead::Vector3f _1c = sead::Vector3f::ez;
    /* 0x28 */ f32 _28 = 1.0f;
    /* 0x2c */ sead::Vector4f _2c = {0, 0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(Unk_71024f67a8, 0x40);

}  // namespace ksys::phys
