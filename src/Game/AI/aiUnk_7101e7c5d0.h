#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder name (no name known): a const f32 (0.5f) with external linkage in .rodata, read through
// the GOT by the Player ladder actions (PlayerLadderMove / JumpLand / DownStart / UpStart / UpEnd /
// Jump) and ai::PlayerLadder::calc_. The next constants (0x7101e7c5d4: 0.38f) belong to the same
// group.
// 0x7101e7c1dc: 0.05f (the slow-time scale read by getNoSlowTimeRatio).
extern const f32 sUnk_7101e7c1dc;
extern const f32 sUnk_7101e7c5c4;  // 0.35f
extern const f32 sUnk_7101e7c5c8;  // 1.4f
extern const f32 sUnk_7101e7c5d0;
extern const f32 sUnk_7101e7c5d4;  // 0.38f
extern const f32 sUnk_7101e7c5d8;  // 0.2f

}  // namespace uking
