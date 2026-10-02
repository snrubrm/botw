#include "Game/AI/Behavior/behaviorSetChemicalOffensive.h"

namespace uking::behavior {

SetChemicalOffensive::SetChemicalOffensive(const InitArg& arg) : SetChemicalPower(arg) {}

SetChemicalOffensive::~SetChemicalOffensive() = default;

bool SetChemicalOffensive::m6(sead::Heap* heap) {
    return SetChemicalPower::m6(heap);
}

void SetChemicalOffensive::m7() {
    SetChemicalPower::m7();
}

void SetChemicalOffensive::m8() {
    SetChemicalPower::m8();
}

void SetChemicalOffensive::m9() {
    SetChemicalPower::m9();
}

void SetChemicalOffensive::loadParams() {
    SetChemicalPower::loadParams();
}

}  // namespace uking::behavior
