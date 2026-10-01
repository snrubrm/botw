#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

EnemyBattle::EnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsUpdateNoticeState_s) {
        auto* actor = mActor;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    }
    _88 = testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1);
    m34(params);
}

bool EnemyBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyBattle::loadParams_() {
    getStaticParam(&mRetFrmGrdAtkTimer_s, "RetFrmGrdAtkTimer");
    getStaticParam(&mRetFrmGrdAtkPrcTimer_s, "RetFrmGrdAtkPrcTimer");
    getStaticParam(&mRetFrmDmgAtkTimer_s, "RetFrmDmgAtkTimer");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mGlobalNoAtkTimeRnd_s, "GlobalNoAtkTimeRnd");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mDisplayCheckRadius_s, "DisplayCheckRadius");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
    getStaticParam(&mIsCheckLineReachable_s, "IsCheckLineReachable");
}

void EnemyBattle::m36(sead::Vector3f* pos) {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(m35(), &acc);
    acc.getActorMtx().getTranslation(*pos);
}

void EnemyBattle::m37() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m36(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘準備", &pack);
}

void EnemyBattle::m38() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m36(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    m43(&pack);
    changeChild("戦闘攻撃", &pack);
}

}  // namespace uking::ai
