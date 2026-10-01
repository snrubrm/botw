#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

namespace uking::act {
class Unk_71002dccbc;
}

// Free helper functions of an unnamed AI utility translation unit (0x71005d6d10 - 0x71005e2f3c,
// linked between aiUrbosasFuryDamageSelector and aiVacuumedBombDamageSelect). Most of them take an
// actor, DynamicCast it (e.g. to uking::act::Enemy) and access the result.
// Names are placeholders (sub_<address>) unless the CSV had one; setDamageCallbackTiming and
// sub_71005DA114 (also in this file) are declared in Game/Damage/dmgDamageCallback.h.

// --- uking::act::Enemy target (Enemy::_c48) ---

/// Enemy target link, or nullptr if the actor is not an Enemy.
ksys::act::BaseProcLink* sub_71005D9050(ksys::act::Actor* actor);
/// Enemy target link, or a global empty BaseProcLink if the actor is not an Enemy.
ksys::act::BaseProcLink& sub_71005D94AC(ksys::act::Actor* actor);
/// Whether the Enemy has a target (link has a proc).
bool sub_71005D8F28(ksys::act::Actor* actor);
/// Whether the Enemy target is the player.
bool sub_71005D8FBC(ksys::act::Actor* actor);
/// Resets the Enemy target link and state.
void sub_71005D8E9C(ksys::act::Actor* actor);
/// Sets the Enemy target (Unk_7100013308::sub_71002DBC8C).
void sub_71005D8DE8(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link,
                    const sead::Matrix34f* mtx, const sead::Vector3f* pos);
/// Enemy target position (Vector3f::zero if not an Enemy).
const sead::Vector3f& sub_71005D9330(ksys::act::Actor* actor);
/// Position of the target actor (getField44C_Vec3), zero if there is none.
const sead::Vector3f& sub_71005D93CC(ksys::act::Actor* actor);
/// Velocity of the target actor, zero if not an Enemy.
const sead::Vector3f& sub_71005D9548(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D960C(ksys::act::Actor* actor);
const sead::Matrix34f& sub_71005D96A8(ksys::act::Actor* actor);
/// Enemy target state (0 if not an Enemy).
s32 sub_71005D9744(ksys::act::Actor* actor);
bool sub_71005D97D0(ksys::act::Actor* actor);
const sead::Vector3f& sub_71005D98D8(ksys::act::Actor* actor);
void sub_71005D9974(ksys::act::Actor* actor, u32 mask, bool set);

// --- other uking::act::Enemy fields ---

void sub_71005D7014(ksys::act::Actor* actor);
/// Enemy::_d70 or NPC::_e90 (nullptr otherwise).
uking::act::Unk_71002dccbc* sub_71005D9D68(ksys::act::Actor* actor);
bool sub_71005DAFB0(ksys::act::Actor* actor);
