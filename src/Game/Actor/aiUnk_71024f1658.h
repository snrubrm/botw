#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// Placeholder (vtable 0x71024f1658, size 0x7b8, constructor 0x7100eec734; the object holds an array of 0x20 fixed
// strings from +0x78): the large embedded object of NPCTravel (+0x1f8) and AssassinRoot (+0x290) that
// NPCBase::_840 points to. Only the members that the AIs call are declared (all declaration only).
class Unk_71024f1658 {
public:
    // 0x7100eec734
    Unk_71024f1658();
    // 0x7100eedda4: `position` is the actor's position.
    bool sub_7100EEDDA4(const sead::Vector3f& position);

private:
    alignas(8) u8 _0[0x7b8];
};
static_assert(sizeof(Unk_71024f1658) == 0x7b8);
