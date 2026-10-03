#pragma once

#include <basis/seadTypes.h>

// Unnamed float constants (0x7101e7c2b4 / 0x7101e7c2b8, 20.0 and 50.0; read by PlayerLandDamage::enter_ and
// AI_AI_PlayerNormal::x): the range of fall heights that map to the land damage wait time. Placeholder names =
// address; the defining TU is unknown.
namespace uking {
extern const f32 sUnk_7101e7c2b4;
extern const f32 sUnk_7101e7c2b8;
}  // namespace uking
