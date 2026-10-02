#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
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
