#pragma once

#include <basis/seadTypes.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// Inline-only in the original; name and form are guesses. A countdown timer (f32 value) with an integer range
// the next value is drawn from. Evidence (lane1 s26): AddSwarmMove::calc_ (0x94) and
// LynelEscapeFromTarget::calc_ (0x60) keep `this + offset` in one register for the update / store / test and
// load the two integers as an `ldp` pair, which a plain f32 member plus two ints does not reproduce.
struct RandomTimer {
    f32 value = 0;
    s32 min = 0;
    s32 max = 0;

    void reset() {
        s32 new_value = min;
        if (max != min)
            new_value = sead::GlobalRandom::instance()->getS32Range(min, max);
        value = f32(new_value);
    }
    void update() { ksys::Timer::update(&value, -1.0f); }
};

}  // namespace uking::ai
