#include "Game/AI/Behavior/behaviorEnemyKeepAnimeDriven.h"

namespace uking::behavior {

EnemyKeepAnimeDriven::EnemyKeepAnimeDriven(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
EnemyKeepAnimeDriven::~EnemyKeepAnimeDriven() {
    ;
}

bool EnemyKeepAnimeDriven::m6(sead::Heap* heap) {
    return true;
}

void EnemyKeepAnimeDriven::m7() {}

void EnemyKeepAnimeDriven::loadParams() {
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

}  // namespace uking::behavior
