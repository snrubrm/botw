#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71023f18e8.h"

Unk_7100a921fc::Unk_7100a921fc() = default;

void Unk_7100a921fc::sub_7100A92208(s32 count) {
    _8 = count;
    _0 = _4 = sead::GlobalRandom::instance()->getU32(count);
}

// NON_MATCHING: the original computes `count - 1` before the modulo (kept in a callee-saved register);
// `const s32 last = count - 1;` as a local would match (borderline, not applied)
bool Unk_7100a921fc::sub_7100A92248() {
    const s32 start = _0;
    const s32 prev = _4;
    const s32 count = _8;
    _4 = (prev + 1) % count;
    if (_4 == start)
        _0 = _4 = sead::GlobalRandom::instance()->getU32(count);
    return prev == count - 1;
}
