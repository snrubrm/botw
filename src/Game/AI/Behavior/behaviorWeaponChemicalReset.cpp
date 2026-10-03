#include "Game/AI/Behavior/behaviorWeaponChemicalReset.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::behavior {

WeaponChemicalReset::WeaponChemicalReset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

WeaponChemicalReset::~WeaponChemicalReset() = default;

bool WeaponChemicalReset::m6(sead::Heap* heap) {
    return true;
}

void WeaponChemicalReset::m7() {}

// NON_MATCHING: the 2 passed by reference lives at sp+8 in the original (sp+0xc here); everything else is identical
void WeaponChemicalReset::m8() {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        actor->getWeapons();
        const s32 state = 2;
        for (int i = 0; i < 6; ++i) {
            auto* weapon =
                sead::DynamicCast<uking::act::Weapon>(actor->getWeapons()->getEquippedWeapon(i));
            if (weapon)
                weapon->sub_71002EDB3C(state);
        }
    }
}

void WeaponChemicalReset::m9() {}

void WeaponChemicalReset::loadParams() {

}

}  // namespace uking::behavior
