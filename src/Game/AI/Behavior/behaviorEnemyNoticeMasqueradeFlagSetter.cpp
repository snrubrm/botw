#include "Game/AI/Behavior/behaviorEnemyNoticeMasqueradeFlagSetter.h"

namespace uking::behavior {

EnemyNoticeMasqueradeFlagSetter::EnemyNoticeMasqueradeFlagSetter(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

EnemyNoticeMasqueradeFlagSetter::~EnemyNoticeMasqueradeFlagSetter() = default;

bool EnemyNoticeMasqueradeFlagSetter::m6(sead::Heap* heap) {
    return true;
}

void EnemyNoticeMasqueradeFlagSetter::m7() {}

void EnemyNoticeMasqueradeFlagSetter::loadParams() {
    getStaticParam(&mTiming_s, "Timing");
    getStaticParam(&mIsOn_s, "IsOn");
}

}  // namespace uking::behavior
