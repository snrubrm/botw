#pragma once

#include <basis/seadTypes.h>

// Unnamed float constants (0x7101e7c2b4 / 0x7101e7c2b8, 20.0 and 50.0; read by PlayerLandDamage::enter_ and
// AI_AI_PlayerNormal::x): the range of fall heights that map to the land damage wait time. Placeholder names =
// address; the defining TU is unknown.
namespace uking {
// 0x7101e7c2b0 (30): the s32 just before the two floats; read by Player::sub_7100884578 (converted to f32).
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
