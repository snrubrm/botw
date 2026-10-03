#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

// Free functions of an unnamed AI utility translation unit (0x71007368a4 - 0x710073f000). Names are
// placeholders unless noted.

/// 0x710073bcb4 (placeholder name): whether the pause menu's section of the weapon type has room.
bool sub_710073BCB4(const sead::SafeString& weapon_type);

/// 0x710073d258 (placeholder name): flips the game data bool "Fire_Relic_PlayerWhistle".
void sub_710073D258();

/// 0x710073d2b4 (placeholder name): queues a camera rumble request (Vibration::Unk2).
void sub_710073D2B4(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6,
                    const sead::Vector3f& a7, u8 a8);

/// 0x710073d488 (CSV BaseProcLink::getEnemyRank): the enemy rank of the linked actor.
s32 getEnemyRank(ksys::act::BaseProcLink* link);

/// 0x710073d4d4 (placeholder name): the pointer stored in the AI tree variable `name` of the actor's root AI
/// (null if there is none).
void* sub_710073D4D4(ksys::act::Actor* actor, const sead::SafeString& name);
