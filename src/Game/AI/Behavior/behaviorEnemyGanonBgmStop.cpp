#include "Game/AI/Behavior/behaviorEnemyGanonBgmStop.h"

namespace uking::behavior {

EnemyGanonBgmStop::EnemyGanonBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EnemyGanonBgmStop::~EnemyGanonBgmStop() = default;

bool EnemyGanonBgmStop::m6(sead::Heap* heap) {
    return true;
}

void EnemyGanonBgmStop::m9() {}

void EnemyGanonBgmStop::loadParams() {

}

void EnemyGanonBgmStop::m8() {
    _28 = false;
}

}  // namespace uking::behavior
