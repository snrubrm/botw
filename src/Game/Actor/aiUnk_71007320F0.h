#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// Free helpers of an unnamed AI utility translation unit around 0x7100731000 (enemy defeat
// counters, dropped weapon flags, weapon ranges). Names are placeholders.

/// Weapon range for the slot, or the actor's attack range if no weapon is equipped.
f32 sub_71007320F0(ksys::act::Actor* actor, int weapon_idx);
/// Like sub_71007320F0, used for the just-avoid distance of attacks.
f32 sub_71007322E8(ksys::act::Actor* actor, int weapon_idx);
