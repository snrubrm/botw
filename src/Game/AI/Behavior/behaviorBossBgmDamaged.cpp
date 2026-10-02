#include "Game/AI/Behavior/behaviorBossBgmDamaged.h"

namespace uking::behavior {

BossBgmDamaged::BossBgmDamaged(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BossBgmDamaged::~BossBgmDamaged() = default;

bool BossBgmDamaged::m6(sead::Heap* heap) {
    return true;
}

void BossBgmDamaged::m8() {}

void BossBgmDamaged::m9() {}

void BossBgmDamaged::loadParams() {
    getStaticParam(&mDieType_s, "DieType");
}

}  // namespace uking::behavior
