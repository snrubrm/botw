#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// Placeholder name (no name known; method 0x7100709414): a small state object embedded in
// AddNoUseTerritoryCounter (+0x40) and ForkLodNoCountTimer (+0x50): a countdown (`_10`, in frames,
// updated by `sub_7100709414()` with the camera distance `_14` as the limit) of the owner actor.
struct Unk_7100709414 {
    explicit Unk_7100709414(ksys::act::Actor* actor) : _8(actor) {}

    // 0x7100709414 (declared only; 224 B): counts `_10` down while the actor is not in the camera range.
    void sub_7100709414();

    s32 _0 = -1;  // 2 = done
    ksys::act::Actor* _8;
    f32 _10 = 0.0f;
    f32 _14 = -1.0f;
    s32 _18 = 0;
    s32 _1c = 0;
};
static_assert(sizeof(Unk_7100709414) == 0x20);
