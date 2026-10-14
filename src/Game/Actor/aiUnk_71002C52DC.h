#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

/// 0x71002c52dc: whether the actor's current life is at most `ratio` of its maximum life reduced by 1000 per
/// cleared Divine Beast (the Calamity Ganon half-life check, EmitGanonHalfLifeDamageSe). Placeholder name.
bool sub_71002C52DC(ksys::act::Actor* actor, f32 ratio);
