#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// Free helpers of an unnamed AI utility translation unit around 0x7100731000 (enemy defeat
// counters, dropped weapon flags, weapon ranges). Names are placeholders.

/// Weapon range of the weapon equipped in slot `weapon_idx` (0 if idx < 0 or there is no weapon).
f32 sub_71007320F0(ksys::act::Actor* actor, int weapon_idx);
/// Like sub_71007320F0, used for the just-avoid distance of attacks.
f32 sub_71007322E8(ksys::act::Actor* actor, int weapon_idx);
