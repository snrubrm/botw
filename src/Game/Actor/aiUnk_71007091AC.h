#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// 0x71007091ac: compares the actor model's local axis (matrix column 2) with the "Neck" bone's
// world matrix column 2 (both normalised): if the angle between them is within 50 degrees the
// outputs are (0, 1, 2), otherwise they are (2, 0, 1) / (1, 2, 0) depending on which side the
// bone points to. Returns false (and sets all outputs to -1) if the actor has no model or no
// "Neck" bone. Used by the GuardianMini* AIs (9 callers) to pick a state parameter set.
// Placeholder name: the purpose of the three outputs is unknown.
bool sub_71007091AC(ksys::act::Actor* actor, s32* out_a, s32* out_b, s32* out_c);

// 0x710070914c: 1 if `out_a` of sub_71007091AC equals `value`, 2 if `out_b` does, otherwise -1.
s32 sub_710070914C(ksys::act::Actor* actor, s32 value);
