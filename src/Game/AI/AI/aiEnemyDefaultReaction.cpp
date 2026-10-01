#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyDefaultReaction::EnemyDefaultReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyDefaultReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyDefaultReaction::leave_() {
    if (_62)
        ksys::act::enableAttClient(mActor, "Grab");
    _58 = -1;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
}

void EnemyDefaultReaction::loadParams_() {
    getStaticParam(&mJustGuardTimesMin_s, "JustGuardTimesMin");
    getStaticParam(&mJustGuardTimesMax_s, "JustGuardTimesMax");
    getStaticParam(&mSmallDamageCancelTimes_s, "SmallDamageCancelTimes");
    getStaticParam(&mInComboSmallDamageNoCancel_s, "InComboSmallDamageNoCancel");
}

bool EnemyDefaultReaction::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EnemyDefaultReaction::m37() {
    return isCurrentChild("死亡");
}

bool EnemyDefaultReaction::m38(dmg::DamageManagerBase* damage_mgr) {
    return damage_mgr->getField50() == 1;
}

void EnemyDefaultReaction::m39(ksys::act::ai::InlineParamPack* params) {
    changeChild("突風", params);
}

void EnemyDefaultReaction::m41(ksys::act::ai::InlineParamPack* params) {
    changeChild("崩れ落ち", params);
}

void EnemyDefaultReaction::m43(ksys::act::ai::InlineParamPack* params) {
    changeChild("大落下", params);
}

void EnemyDefaultReaction::m44() {
    _60 = true;
    _61 = false;
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

}  // namespace uking::ai
