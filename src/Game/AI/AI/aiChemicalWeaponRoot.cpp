#include "Game/AI/AI/aiChemicalWeaponRoot.h"

namespace uking::ai {

ChemicalWeaponRoot::ChemicalWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

ChemicalWeaponRoot::~ChemicalWeaponRoot() = default;

void ChemicalWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    _e8 = true;
    _ec = -1;
    m44();
}

}  // namespace uking::ai
