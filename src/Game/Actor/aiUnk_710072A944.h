#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actSwarm.h"

namespace ksys::act {
class Actor;
}

namespace uking::act {
class Swarm;
}

// Swarm helpers in the translation unit around 0x710072a8c4 (CSV swarmDropTableStuff). Placeholder
// names; not decompiled yet.

// 0x7100729370: sums the opposite contact directions of the four swarm bodies.
void sub_7100729370(uking::act::Swarm* swarm, sead::Vector3f* direction, s32* count);

void swarmDropTableStuff(ksys::act::Actor* actor);
void sub_710072A264(uking::act::Swarm* swarm, const sead::Vector3f& target, const sead::Vector3f& up);
void sub_710072A3BC(uking::act::Swarm* swarm, const sead::Vector3f& target, const sead::Vector3f& up);
void sub_710072A514(uking::act::Swarm* swarm, const sead::Vector3f& front, const sead::Vector3f& up);
void sub_710072A5F8(uking::act::Swarm* swarm, const sead::Vector3f& front, const sead::Vector3f& up);

// 0x710072a944: gives every unit of the swarm a random _5c in [min, max].
void sub_710072A944(uking::act::Swarm* swarm, f32 min, f32 max);

// 0x7100729ea8 (declared only; 140 B): ForkSwarmAttack / SwarmFlyAttack enter_ (loops over the swarm's unit bodies
// and calls sub_71007A2B64(body, translation or nullptr) on each).
void sub_7100729EA8(uking::act::Swarm* swarm);

// 0x7100729f34 (declared only; 120 B): ForkSwarmAttack / SwarmFlyAttack leave_ (loops over the swarm's unit bodies
// and calls sub_71007A2D34 on each).
void sub_7100729F34(uking::act::Swarm* swarm);
// Full 72AA48 and independent Bee reaction methods pass the signed damage type.
s32 sub_710072AA48(ksys::act::Actor* actor, s32 type);
// Full 72AAE4 and BeeDamaged::enter_ remove the swarm unit bodies from the world.
void sub_710072AAE4(ksys::act::Actor* actor);

// 0x710072abb4 (208 B): BeeDamaged::leave_.
void sub_710072ABB4(ksys::act::Actor* actor);

// 0x710072a6dc (156 B): the swarm unit nearest to `pos` among those without state bit 0 (null if none);
// SwarmDamaged::m33.
uking::act::Swarm::Unit* sub_710072A6DC(uking::act::Swarm* swarm, const sead::Vector3f& pos);

// 0x7100729d5c (declared only; 68 B): sibling of sub_7100729D18 (same body 0x7100729568 with a different local helper object);
// the swarm movement step of the SwarmDamaged family's m32 (`speed`, the swarm, three optional arguments: the third is
// a position, flag). The result is discarded by its callers.
bool sub_7100729D5C(f32 speed, uking::act::Swarm* swarm, void* a, const sead::Vector3f* pos, void* b, bool flag);
// 0x7100729fac (348 B): SwarmAreaDamaged::m32.
void sub_7100729FAC(uking::act::Swarm* swarm, const sead::Vector3f& dir);
// 0x710072a108 (348 B): SwarmDamagedBase::m32.
void sub_710072A108(uking::act::Swarm* swarm, const sead::Vector3f& dir);
// 0x710072a778 (declared only; 148 B): SwarmLevelFlyMove::enter_ (swarm, material animation name, frame).
void sub_710072A778(uking::act::Swarm* swarm, const sead::SafeString& name, f32 frame);

