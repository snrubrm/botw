#include "Game/AI/Behavior/behaviorAnimalAttack.h"

namespace uking::behavior {

AnimalAttack::AnimalAttack(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
AnimalAttack::~AnimalAttack() {
    ;
}

bool AnimalAttack::m6(sead::Heap* heap) {
    return true;
}

void AnimalAttack::loadParams() {
    getStaticParam(&mIsUseASEventAtCollision_s, "IsUseASEventAtCollision");
    getStaticParam(&mAtkRigidName_s, "AtkRigidName");
}

}  // namespace uking::behavior
