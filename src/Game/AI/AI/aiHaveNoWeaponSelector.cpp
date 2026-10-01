#include "Game/AI/AI/aiHaveNoWeaponSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

HaveNoWeaponSelector::HaveNoWeaponSelector(const InitArg& arg) : EquipHaveSelector(arg) {}

HaveNoWeaponSelector::~HaveNoWeaponSelector() = default;

bool HaveNoWeaponSelector::m34() {
    return sub_71005D8B60(mActor);
}

}  // namespace uking::ai
