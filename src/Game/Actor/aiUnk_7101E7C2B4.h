#pragma once

#include <basis/seadTypes.h>

// Unnamed float constants (0x7101e7c2b4 / 0x7101e7c2b8, 20.0 and 50.0; read by PlayerLandDamage::enter_ and
// AI_AI_PlayerNormal::x): the range of fall heights that map to the land damage wait time. Placeholder names =
// address; the defining TU is unknown.
namespace uking {
// 0x7101e7c2b0 (30): the s32 just before the two floats; read by Player::sub_7100884578 (converted to f32).
// 0x7101e7c244 / 0x7101e7c248 (5.0, 0.5): read by Player::m69_x_6 (push-down vector from _216c).
extern const f32 sUnk_7101e7c244;
extern const f32 sUnk_7101e7c248;
// 0x7101e7c24c (0.3): read by Player::actionCommon (character controller rate, divided by _20f0 in slow time).
extern const f32 sUnk_7101e7c24c;
// 0x7101e7c280 - 0x7101e7c29c (9, 9, 9, 9, 3, 3, 3, 3): the champion ability Plus support timer rates inside / outside
// Hyrule Castle (wind, fire, electric, water; Player::updateSupportTimerRates).
extern const f32 sUnk_7101e7c280;
extern const f32 sUnk_7101e7c284;
extern const f32 sUnk_7101e7c288;
extern const f32 sUnk_7101e7c28c;
extern const f32 sUnk_7101e7c290;
extern const f32 sUnk_7101e7c294;
extern const f32 sUnk_7101e7c298;
extern const f32 sUnk_7101e7c29c;
// 0x7101e7c2a0 (5.27): speed limit (per second) of the ridden actor in PlayerBase::sub_7100849198.
extern const f32 sUnk_7101e7c2a0;
// 0x7101e7c2a8 (3.2): read by Player::x_30 (bow slow invalid height with PlayerBase::x_48).
extern const f32 sUnk_7101e7c2a8;
extern const s32 sUnk_7101e7c2b0;
extern const f32 sUnk_7101e7c2b4;
extern const f32 sUnk_7101e7c2b8;
// 0x7101e7c2d8 / 0x7101e7c2dc (-0.4, 0.2): read by Player::sub_71008838FC.
extern const f32 sUnk_7101e7c2d8;
extern const f32 sUnk_7101e7c2dc;
// 0x7101e7c2f8 (49.5, degrees): read by Player::sub_7100892098 / sub_710086D5B8 / PlayerSlide::calc_.
extern const f32 sUnk_7101e7c2f8;
}  // namespace uking
