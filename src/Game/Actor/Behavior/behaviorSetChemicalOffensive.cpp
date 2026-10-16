#include "Game/Actor/Behavior/behaviorSetChemicalOffensive.h"

namespace uking::behavior {

SetChemicalOffensive::SetChemicalOffensive(const InitArg& arg) : SetChemicalPower(arg) {}

SetChemicalOffensive::~SetChemicalOffensive() = default;

bool SetChemicalOffensive::init_(sead::Heap* heap) {
    return SetChemicalPower::init_(heap);
}

void SetChemicalOffensive::calc() {
    SetChemicalPower::calc();
}

void SetChemicalOffensive::enter() {
    SetChemicalPower::enter();
}

void SetChemicalOffensive::leave() {
    SetChemicalPower::leave();
}

void SetChemicalOffensive::loadParams() {
    SetChemicalPower::loadParams();
}

}  // namespace uking::behavior
