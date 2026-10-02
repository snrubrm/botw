#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder name (no name known): a const f32 (0.5f) with external linkage in .rodata, read through
// the GOT by the Player ladder actions (PlayerLadderMove / JumpLand / DownStart / UpStart / UpEnd /
// Jump) and ai::PlayerLadder::calc_. The next constants (0x7101e7c5d4: 0.38f) belong to the same
// group.
extern const f32 sUnk_7101e7c5d0;

}  // namespace uking
