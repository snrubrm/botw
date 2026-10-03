#pragma once

namespace ksys::act {
class Actor;
}

// Player AI helpers (TU 0x710087c000-0x710087fff0, lane2 s21; placeholder names = addresses).

// 0x710087ce34: enables the character controller's EntityGround / EntityGroundRough / EntityGroundObject /
// EntityTree contact layers (no-op without a controller).
void sub_710087CE34(ksys::act::Actor* actor);

// 0x710087ce90: disables the same four contact layers.
void sub_710087CE90(ksys::act::Actor* actor);

// 0x7100873264 / 0x71008732c8: add the "Head" body of the actor's "Tgt" body set to the physics world /
// remove it again (no-op if either is missing).
void sub_7100873264(ksys::act::Actor* actor);
void sub_71008732C8(ksys::act::Actor* actor);
