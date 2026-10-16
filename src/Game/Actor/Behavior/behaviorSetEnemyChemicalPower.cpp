#include "Game/Actor/Behavior/behaviorSetEnemyChemicalPower.h"
#include "Game/Actor/aiUnk_71006F5B14.h"

namespace uking::behavior {

SetEnemyChemicalPower::SetEnemyChemicalPower(const InitArg& arg) : SetChemicalPower(arg) {}

SetEnemyChemicalPower::~SetEnemyChemicalPower() = default;

bool SetEnemyChemicalPower::init_(sead::Heap* heap) {
    return SetChemicalPower::init_(heap);
}

void SetEnemyChemicalPower::calc() {
    SetChemicalPower::calc();
}

void SetEnemyChemicalPower::enter() {
    SetChemicalPower::enter();
}

void SetEnemyChemicalPower::leave() {
    SetChemicalPower::leave();
}

void SetEnemyChemicalPower::loadParams() {
    SetChemicalPower::loadParams();
}

void SetEnemyChemicalPower::m14(bool on) {
    if (on)
        sub_71006F5C50(mActor);
    else
        sub_71006F5B14(mActor);
}

}  // namespace uking::behavior
