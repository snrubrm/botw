#pragma once

#include <math/seadVector.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

/// inline-only in the original; name is a guess. Evidence: the same sequence (a PlayerOrEnemy's
/// equipped weapon `weapon_idx`, `goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0)`) repeats three
/// times in each of GuardianMiniWait::m32 and GuardianMiniGuardWait::m32. Returns the weapon, or
/// nullptr if there is none.
static inline uking::act::Weapon* goLimpWithWeaponProfile(ksys::act::Actor* actor, ksys::as::ASList* list,
                                                   int weapon_idx) {
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor)) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(
            actor->getWeapons()->getEquippedWeapon(weapon_idx));
        if (weapon) {
            list->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
            return weapon;
        }
    }
    return nullptr;
}

}  // namespace uking::action
