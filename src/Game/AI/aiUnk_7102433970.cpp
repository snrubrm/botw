#include "Game/AI/aiUnk_7102433970.h"

Unk_7100743798::Unk_7100743798()
    : _0(-1), _e0(0.0f, 0.0f), _13c(0), _140(false), _141(false) {}

bool Unk_7100743798::sub_7100743814(ksys::act::Actor* actor) {
    _8.sub_7100721830(actor, true);
    _0 = -1;
    _e0.reset(0.0f);
    _13c = 0;
    _140 = false;
    _141 = false;
    for (auto& permutation : mPermutations)
        permutation.init(5);
    mPermutations[4].init(9);
    mPermutations[6].init(8);
    return true;
}

// 0x7100744200: switches to `mode` (unless one is already set and `force` is false). Mode 1 restarts the timer
// `_e0` at 90 (or keeps its current value if that is larger) with the default rate.
void Unk_7100743798::sub_7100744200(s32 mode, bool force) {
    if (_0 != -1 && !force)
        return;
    f32 value = mode == 1 ? 90.0f : 0.0f;
    _0 = mode;
    if (mode != 1)
        return;
    value = value > _e0.value ? value : _e0.value;
    _e0 = ksys::Timer(value, value);
}
