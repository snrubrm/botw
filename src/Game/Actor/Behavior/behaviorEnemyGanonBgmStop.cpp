#include "Game/Actor/Behavior/behaviorEnemyGanonBgmStop.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EnemyGanonBgmStop::EnemyGanonBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EnemyGanonBgmStop::~EnemyGanonBgmStop() = default;

bool EnemyGanonBgmStop::init_(sead::Heap* heap) {
    return true;
}

void EnemyGanonBgmStop::leave() {}

void EnemyGanonBgmStop::loadParams() {

}

void EnemyGanonBgmStop::calc() {
    auto* life = mActor->getLife();
    if (life && *life == 0 && !_28) {
        _28 = true;
        if (auto* bgm = sub_7100FFE6EC())
            bgm->sub_7101010C58(1.0f);
    }
}

void EnemyGanonBgmStop::enter() {
    _28 = false;
}

}  // namespace uking::behavior
