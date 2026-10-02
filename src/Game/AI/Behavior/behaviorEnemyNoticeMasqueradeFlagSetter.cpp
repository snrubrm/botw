#include "Game/AI/Behavior/behaviorEnemyNoticeMasqueradeFlagSetter.h"
#include "Game/Actor/actEnemy.h"

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

void EnemyNoticeMasqueradeFlagSetter::m8() {
    if (*mTiming_s != 0)
        return;
    const bool on = *mIsOn_s;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.change(2, on);
}

void EnemyNoticeMasqueradeFlagSetter::m9() {
    if (*mTiming_s != 1)
        return;
    const bool on = *mIsOn_s;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.change(2, on);
}

}  // namespace uking::behavior
