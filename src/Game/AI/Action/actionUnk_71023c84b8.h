#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionUnk_71023c8568.h"

// Turn helper with a fixed target position (vtable 0x71023c84b8, ctor 0x71002a68b0) embedded in
// AssassinBossIronBallAtkWithRot.
class Unk_71023c84b8 : public Unk_71023c8568 {
    SEAD_RTTI_OVERRIDE(Unk_71023c84b8, Unk_71023c8568)
public:
    explicit Unk_71023c84b8(ksys::act::ai::ActionBase* owner);

    void m13(sead::Vector3f* target) override { *target = _5c; }

    sead::Vector3f _5c = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(Unk_71023c84b8, 0x68);
