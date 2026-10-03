#pragma once

namespace ksys::act {
class Actor;
}

// GanonBeast helper TU at 0x71007028xx (lane1 s21). Placeholder name.

// 0x710070284c: the GanonBeast stage (0 - 3) of the actor, from its life (getLife(); 1 without a
// life pointer): lookup table {3, 3, 2, 1, 1, 1, 0, 0, 0}, 0 when above 8.
int sub_710070284C(ksys::act::Actor* actor);

// Small life predicates of the same TU (lane4 s22; evidence: asm of 0x71007028cc / 0x7100702894 /
// 0x7100703bc8, all `getLife()` (Actor vslot 87) then a test of the value).
// 0x7100702894: the life is 1 (true without a life pointer).
bool sub_7100702894(ksys::act::Actor* actor);
// 0x71007028cc: the life is below 1 (false without a life pointer).
bool sub_71007028CC(ksys::act::Actor* actor);
// 0x7100703bc8: the life is 1, 2 or 5 (1 without a life pointer).
bool sub_7100703BC8(ksys::act::Actor* actor);
