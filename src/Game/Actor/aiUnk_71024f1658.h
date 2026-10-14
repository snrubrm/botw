#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_71024f15c0.h"

namespace ksys::act {
class Actor;
}

// Placeholder (vtable 0x71024f1658, size 0x7b8, constructor 0x7100eec734): the large embedded object of
// NPCTravel (+0x1f8) and AssassinRoot (+0x290) that NPCBase::_840 points to. Derives from Unk_71024f15c0
// (the constructor inlines its base constructor; slots 2-4 override m2 / m3 / m4). Its functions at
// 0x7100eee19c-0x7100eeef60 read the actor's Traveler gparam object (GParamList type 0x29) through tables
// of getter member pointers at 0x71024f17b0, indexed by _70 (route point) and the sign of _72 (direction).
// Only the members that other classes call are declared (all declaration only).
class Unk_71024f1658 : public Unk_71024f15c0 {
public:
    // 0x7100eec734
    Unk_71024f1658();
    // 0x7100eedda4: `position` is the actor's position.
    bool sub_7100EEDDA4(const sead::Vector3f& position);
    // 0x7100eeee88: a Traveler route string for the current point and direction ("" if the actor
    // has no Traveler parameters or _71 < 2).
    const char* sub_7100EEEE88(ksys::act::Actor* actor);

    /* 0x60 */ sead::SafeString _60;
    /* 0x70 */ s8 _70 = -1;
    /* 0x71 */ s8 _71 = 0;
    /* 0x72 */ s8 _72 = 1;
    /* 0x78 */ sead::SafeArray<sead::FixedSafeString<32>, 32> _78;
    /* 0x778 */ u8 _778[0x40];
};
static_assert(sizeof(Unk_71024f1658) == 0x7b8);
