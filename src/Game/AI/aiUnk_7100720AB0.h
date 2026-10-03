#pragma once

#include <basis/seadTypes.h>
#include <container/seadRingBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Placeholder name = constructor address (0x7100720ab0; no real name known). 0x50-byte helper
// embedded in ForkSeqNoWeaponAttack (+0x80), SeqPunchByASEvent (+0x50) and MoveRemainsElectric: its
// calc (0x7100720b28) enumerates the actor's active attack AS entries and calls
// sub_71007A2D7C(actor, name) for the names found, its leave (0x7100720fd0) does the same for the
// ones it started. None of its methods except the constructor / destructor is decompiled.
class Unk_7100720ab0 {
public:
    explicit Unk_7100720ab0(ksys::act::Actor* actor);
    // 0x7100720af0: out of line, empty.
    ~Unk_7100720ab0();

    // 0x7100720af4 (declared only): _8 = a value of the actor's param list (index 8, +0x70); _10 = 0.
    void sub_7100720AF4();
    // 0x7100720b28 / 0x7100720fd0 (declared only)
    void sub_7100720B28();
    void sub_7100720FD0();

    /* 0x00 */ ksys::act::Actor* mActor;
    /* 0x08 */ u32 _8 = 0;
    /* 0x0c */ u32 _c = 0x2000;
    /* 0x10 */ u32 _10 = 0;
    /* 0x18 */ sead::FixedRingBuffer<sead::SafeString, 2> _18;
};
KSYS_CHECK_SIZE_NX150(Unk_7100720ab0, 0x50);
