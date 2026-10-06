#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"

// The embedded helper object of MoveByAnimeDrivenToTarget (its TU starts at 0x7100000fd0).
Unk_7100000fd0::~Unk_7100000fd0() = default;

// NON_MATCHING: the original stores the z component (wzr) before the 8-byte xy store (ours: xy first)
void Unk_7100000fd0::sub_710000102C(f32 value) {
    _30.set(0.0f, 0.0f, 0.0f);
    _48 = value;
}

// NON_MATCHING: store order of the zeroed vector (original: z, then xy) and the load of other._48 first
void Unk_7100000fd0::sub_710000103C(const Unk_7100000fd0& other) {
    _30.set(0.0f, 0.0f, 0.0f);
    _48 = other._48;
}
