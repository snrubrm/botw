#include "Game/AI/Behavior/behaviorEnemyGanonBgmStop.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EnemyGanonBgmStop::EnemyGanonBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EnemyGanonBgmStop::~EnemyGanonBgmStop() = default;

bool EnemyGanonBgmStop::m6(sead::Heap* heap) {
    return true;
}

void EnemyGanonBgmStop::m9() {}

void EnemyGanonBgmStop::loadParams() {

}

void EnemyGanonBgmStop::m7() {
    auto* life = mActor->getLife();
    if (life && *life == 0 && !_28) {
        _28 = true;
        if (auto* bgm = sub_7100FFE6EC())
            bgm->sub_7101010C58(1.0f);
    }
}

void EnemyGanonBgmStop::m8() {
    _28 = false;
}

}  // namespace uking::behavior
