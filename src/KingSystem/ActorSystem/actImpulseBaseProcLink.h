#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Name from Actor::mImpulseBaseProcLink (Actor+0x708). Allocated with new(0x70) by the actor's init
// (0x71011d2904, ctor inlined); the actor's finalisation resets the link and deletes it. Callers keep
// pointers to the impulse data at +0x10 (e.g. Player+0x17f0).
class ImpulseBaseProcLink {
public:
    // Placeholder: the impulse data (types from the ctor stores and the readers:
    // ExceededImpulseCheck::calc_ compares _8 / _c with 0).
    struct Unk1 {
        /* 0x00 */ f32 _0 = 0;
        /* 0x04 */ f32 _4 = 0;
        /* 0x08 */ f32 _8 = 0;
        /* 0x0c */ f32 _c = 0;
        /* 0x10 */ sead::Vector3f _10 = sead::Vector3f::ez;
        /* 0x1c */ sead::Matrix34f _1c = sead::Matrix34f::ident;
        /* 0x4c */ sead::Vector3f _4c = sead::Vector3f::zero;
        /* 0x58 */ u32 _58 = 0;
        /* 0x5c */ u16 _5c = 0;
    };

    // 0x71011d8260 (declared only; placeholder name; ~1.1 KB): called by Actor::m35.
    void sub_71011D8260();

    /* 0x00 */ BaseProcLink mLink;
    /* 0x10 */ Unk1 _10;
};
KSYS_CHECK_SIZE_NX150(ImpulseBaseProcLink, 0x70);

}  // namespace ksys::act
