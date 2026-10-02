#include "Game/AI/Behavior/behaviorBossBgm.h"

namespace uking::behavior {

BossBgm::BossBgm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BossBgm::~BossBgm() = default;

bool BossBgm::m6(sead::Heap* heap) {
    return true;
}

void BossBgm::m7() {}

void BossBgm::loadParams() {
    getStaticParam(&mBossType_s, "BossType");
}

}  // namespace uking::behavior
