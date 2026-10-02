#include "Game/AI/Behavior/behaviorWeaponChemicalReset.h"

namespace uking::behavior {

WeaponChemicalReset::WeaponChemicalReset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

WeaponChemicalReset::~WeaponChemicalReset() = default;

bool WeaponChemicalReset::m6(sead::Heap* heap) {
    return true;
}

void WeaponChemicalReset::m7() {}

void WeaponChemicalReset::m9() {}

void WeaponChemicalReset::loadParams() {

}

}  // namespace uking::behavior
