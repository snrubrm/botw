#include "Game/AI/Behavior/behaviorSetEnemyChemicalPower.h"
#include "Game/AI/aiUnk_71006F5B14.h"

namespace uking::behavior {

SetEnemyChemicalPower::SetEnemyChemicalPower(const InitArg& arg) : SetChemicalPower(arg) {}

SetEnemyChemicalPower::~SetEnemyChemicalPower() = default;

bool SetEnemyChemicalPower::m6(sead::Heap* heap) {
    return SetChemicalPower::m6(heap);
}

void SetEnemyChemicalPower::m7() {
    SetChemicalPower::m7();
}

void SetEnemyChemicalPower::m8() {
    SetChemicalPower::m8();
}

void SetEnemyChemicalPower::m9() {
    SetChemicalPower::m9();
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
