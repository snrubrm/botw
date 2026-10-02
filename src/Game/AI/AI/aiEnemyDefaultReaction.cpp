#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyDefaultReaction::EnemyDefaultReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyDefaultReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::act::isAttClientEnabled(mActor, "Grab")) {
        _62 = true;
        ksys::act::disableAttClient(mActor, "Grab");
    } else {
        _62 = false;
    }
    m44();
    sub_710038782C(params);
    _5c = *mSmallDamageCancelTimes_s;
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

// NON_MATCHING: the original loads the two params before the GlobalRandom instance (same as
// BokoblinArrowBattle::enter_)
void EnemyDefaultReaction::sub_710038782C(ksys::act::ai::InlineParamPack* params) {
    if (_58 <= 0) {
        _58 = sead::GlobalRandom::instance()->getS32Range(*mJustGuardTimesMin_s,
                                                          *mJustGuardTimesMax_s + 1);
    }

    auto* damage_mgr = sub_710072BA90(mActor);
    s32 damage_type = -1;
    bool flag = false;
    if (damage_mgr) {
        damage_type = damage_mgr->getField54();
        flag = damage_mgr->checkDamageFlags(10);
    }
    mActor->getLife();

    if (m45()) {
        m42(params);
        return;
    }
    m35(damage_mgr, damage_type, flag, params);
}

}  // namespace uking::ai
