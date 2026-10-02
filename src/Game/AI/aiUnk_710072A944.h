#pragma once

#include <basis/seadTypes.h>

namespace uking::act {
class Swarm;
}

// Swarm helpers in the translation unit around 0x710072a8c4 (CSV swarmDropTableStuff). Placeholder
// names; not decompiled yet.

// 0x710072a944: gives every unit of the swarm a random _5c in [min, max].
void sub_710072A944(uking::act::Swarm* swarm, f32 min, f32 max);
