#include "Game/AI/AI/aiChemicalGiantArmorRoot.h"

namespace uking::ai {

ChemicalGiantArmorRoot::ChemicalGiantArmorRoot(const InitArg& arg) : GiantArmorRoot(arg) {}

ChemicalGiantArmorRoot::~ChemicalGiantArmorRoot() = default;

bool ChemicalGiantArmorRoot::init_(sead::Heap* heap) {
    return GiantArmorRoot::init_(heap);
}

void ChemicalGiantArmorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorRoot::enter_(params);
    _48 = false;
    _4c = 0.0f;
}

void ChemicalGiantArmorRoot::leave_() {
    GiantArmorRoot::leave_();
    _48 = false;
    _4c = 0.0f;
}

void ChemicalGiantArmorRoot::loadParams_() {
    GiantArmorRoot::loadParams_();
    getStaticParam(&mElectricTime_s, "ElectricTime");
    getStaticParam(&mElectricDamageScale_s, "ElectricDamageScale");
}

}  // namespace uking::ai
