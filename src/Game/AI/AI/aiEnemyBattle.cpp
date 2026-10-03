#include "Game/AI/AI/aiEnemyBattle.h"
#include <random/seadGlobalRandom.h>
#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
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

bool EnemyBattle::m39() {
    if (!m40())
        return false;
    return sub_7100382558();
}

bool EnemyBattle::sub_7100382558() {
    const f32 base = *mGlobalNoAtkTime_s;
    const s32 random = *mGlobalNoAtkTimeRnd_s;
    const f32 extra = random >= 1 ? f32(sead::GlobalRandom::instance()->getS32Range(0, random)) : 0.0f;
    const s32 time = base + extra;
    if (time < 0)
        return true;
    if (!ksys::act::isPlayerProfile(&m35()))
        return true;
    return dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A40(mActor, time);
}

bool EnemyBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyBattle::leave_() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor) && static_cast<act::Enemy*>(actor)->_e84.isOnBit(0))
        sub_7100381ED4();
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
    ksys::act::acquireActor(&m35(), &acc);
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

ksys::act::BaseProcLink& EnemyBattle::m35() {
    auto* link = sub_71005D9050(mActor);
    if (link != nullptr)
        return *link;
    return ksys::act::getDummyBaseProcLink();
}

void EnemyBattle::sub_7100381ED4() {
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (enemy)
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
}

}  // namespace uking::ai
