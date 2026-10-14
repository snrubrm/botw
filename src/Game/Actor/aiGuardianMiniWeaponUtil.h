#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

// inline-only in the original; names are guesses. The weapon in slot `idx` of the enemy is a Weapon
// whose type (`_cf0`) is 4 / is not 4. Evidence: the identical sequence (getWeapons() virtual call after the
// slot index is read, IsDerivedFrom<Weapon> guard, `_cf0` compare) is repeated twice in each of
// 0x710041cce0, 0x710041d304 and 0x710041d4ec.
inline bool hasType4Weapon(uking::act::Enemy* enemy, s32 idx) {
    auto* weapon = enemy->getWeapons()->getEquippedWeapon(idx);
    if (sead::IsDerivedFrom<uking::act::Weapon>(weapon)) {
        if (static_cast<uking::act::Weapon*>(weapon)->_cf0 == 4)
            return true;
    }
    return false;
}

inline bool hasNonType4Weapon(uking::act::Enemy* enemy, s32 idx) {
    auto* weapon = enemy->getWeapons()->getEquippedWeapon(idx);
    if (sead::IsDerivedFrom<uking::act::Weapon>(weapon)) {
        if (static_cast<uking::act::Weapon*>(weapon)->_cf0 != 4)
            return true;
    }
    return false;
}

}  // namespace uking::ai
