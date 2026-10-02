#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class BaseProc;
class BaseProcLink;
}  // namespace ksys::act

// Free functions of an unnamed AI utility translation unit (0x71007368a4 - 0x7100736e20; its
// neighbours are hasAnimalTypeWolfOrBearTags and the dlc::isOneHitObliterator* helpers).
// Names are placeholders.

/// Whether the actor is a Cucco (tag TypeKokko or actor name "Kokko_Simple").
bool sub_71007368A4(ksys::act::BaseProcLink* link);
/// Bool map unit parameter `name` of the actor (ActorConstDataAccess::sub_71006DE298).
bool sub_710073697C(ksys::act::BaseProcLink* link, const sead::SafeString& name);
/// Bool AI tree variable `name` of the actor (ActorConstDataAccess::sub_71006DE338).
bool sub_71007369D0(ksys::act::BaseProcLink* link, const sead::SafeString& name);
/// The actor's previous position.
sead::Vector3f sub_7100736A24(ksys::act::BaseProcLink* link);
/// `value` is one of 20, 21, 22, 23, 27, 30, 31.
bool sub_7100736B68(int value);
/// `value` is one of 20, 22, 23, 27, 30, 31.
bool sub_7100736B94(int value);
/// `value` is one of 6, 7, 8.
bool sub_7100736BBC(int value);
/// `value` is 25 or 26.
bool sub_7100736BD8(int value);
/// The actor's damage manager reports damage type 2, 1 or 5 (DamageManagerBase::getField54).
bool sub_7100736D98(ksys::act::Actor* actor);

// Further functions of the AI utility code (same placeholder conventions).

/// 0x7100739930: the linked actor's name is in the actor's EnemyRace EscapeAttackedActorType list.
bool sub_7100739930(ksys::act::Actor* actor, ksys::act::BaseProcLink* link);
/// 0x71007399b4: the actor's EnemyRace parameters use target tags (IsUseTargetTag) and the
/// accessed actor has the EnemyTarget tag.
bool sub_71007399B4(ksys::act::Actor* actor, const ksys::act::ActorConstDataAccess& accessor);
/// 0x7100739a10: `name` is one of the actor's EnemyRace TargetActorType entries.
bool sub_7100739A10(ksys::act::Actor* actor, const sead::SafeString& name);
/// 0x7100739e24: the linked actor is something the actor eats: it has one of the EatTarget
/// EatActorTags / FavoriteEatActorTags, or its name is in the comma-separated list selected by
/// `kind` (0: EatActorNames, 1: EatActorNames2, 2: EatActorNames3, 3: FavoriteEatActorNames,
/// other: any of them).
bool sub_7100739E24(ksys::act::Actor* actor, ksys::act::BaseProcLink* link, int kind);
/// 0x710073a010: `proc` is a favourite food of the actor (EatTarget FavoriteEatActorTags /
/// FavoriteEatActorNames).
bool sub_710073A010(ksys::act::Actor* actor, ksys::act::BaseProc* proc);
/// 0x710073d51c (CSV Actor::checkHpRate): whether the actor's life is at most `rate` times its max
/// life (life is 1 without a life value).
bool checkHpRate(ksys::act::Actor* actor, f32 rate);
/// 0x710073d584 (CSV name; declared only).
bool enemyTeamStuff(ksys::act::Actor* actor, ksys::act::BaseProcLink* link);
