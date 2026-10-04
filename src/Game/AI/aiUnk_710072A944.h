#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

namespace uking::act {
class Swarm;
}

// Swarm helpers in the translation unit around 0x710072a8c4 (CSV swarmDropTableStuff). Placeholder
// names; not decompiled yet.

// 0x710072a944: gives every unit of the swarm a random _5c in [min, max].
void sub_710072A944(uking::act::Swarm* swarm, f32 min, f32 max);

// 0x7100729f34 (declared only; 120 B): ForkSwarmAttack / SwarmFlyAttack leave_ (loops over the swarm's unit bodies
// and calls sub_71007A2D34 on each).
void sub_7100729F34(uking::act::Swarm* swarm);
// 0x710072abb4 (declared only; 208 B): BeeDamaged::leave_.
void sub_710072ABB4(ksys::act::Actor* actor);
