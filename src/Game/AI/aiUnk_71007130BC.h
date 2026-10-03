#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// NPC AI helpers (TU 0x7100711000-0x7100714800, lane2 s21; placeholder names = addresses).

// 0x71007130bc: null-safe: `on` -> Actor::x_6() else setEnabledTalkAndLockOn(actor, false).
void sub_71007130BC(ksys::act::Actor* actor, bool on);

// 0x7100713564: for an actor with the tag 0x207cbce1, sets the game data `<actor>_AttackedState` to
// `clamp(count, 0, 3)`.
void sub_7100713564(ksys::act::Actor* actor, s32 count);
