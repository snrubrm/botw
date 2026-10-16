#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder name (no name known): a const f32 (0.5f) with external linkage in .rodata, read through
// the GOT by the Player ladder actions (PlayerLadderMove / JumpLand / DownStart / UpStart / UpEnd /
// Jump) and ai::PlayerLadder::calc_. The next constants (0x7101e7c5d4: 0.38f) belong to the same
// group.
// 0x7101e7c1dc: 0.05f (the slow-time scale read by getNoSlowTimeRatio).
// 0x7101e7c1d8: 1.0f (stamina recovery factor in slow time, Player::sub_710084AD5C).
extern const f32 sUnk_7101e7c1d8;
// 0x7101e7c184 / 0x7101e7c1a4 (0.13f each), 0x7101e7c2e0 (0.19f), 0x7101e7c5bc (1.5f): Player::sub_71008901D0.
extern const f32 sUnk_7101e7c184;
extern const f32 sUnk_7101e7c1a4;
extern const f32 sUnk_7101e7c2e0;
extern const f32 sUnk_7101e7c5bc;
extern const f32 sUnk_7101e7c1dc;
// 0x7101e7c25c: 100.0f (Player::sub_7100893F1C, the cap of _1fe8).
extern const f32 sUnk_7101e7c25c;
// 0x7101e7c268 / 0x7101e7c26c: 0.05f / 0.1f (Player::m310 chase rates up / down).
extern const f32 sUnk_7101e7c268;
extern const f32 sUnk_7101e7c26c;
extern const f32 sUnk_7101e7c5c4;  // 0.35f
extern const f32 sUnk_7101e7c5c8;  // 1.4f
extern const f32 sUnk_7101e7c5d0;
extern const f32 sUnk_7101e7c5d4;  // 0.38f
extern const f32 sUnk_7101e7c5d8;  // 0.2f
// 0x7101e7d6ec / 0x7101e7d6f0: also read through the GOT by EventPickOutFromPorch::enter_ and 0x71008712cc.
extern const f32 sUnk_7101e7d6ec;  // 0.8f
extern const f32 sUnk_7101e7d6f0;  // -0.8f

}  // namespace uking
