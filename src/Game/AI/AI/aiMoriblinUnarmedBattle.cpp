#include "Game/AI/AI/aiMoriblinUnarmedBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MoriblinUnarmedBattle::MoriblinUnarmedBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinUnarmedBattle::~MoriblinUnarmedBattle() = default;

void MoriblinUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    sub_71004AC4F8();
    _b8 = ksys::Timer(0, 0);
}

void MoriblinUnarmedBattle::sub_71004AC4F8() {
    if (sub_7100736D98(mActor) || testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
        if (level && *level->mIsCounterAttack) {
            changeToAttack();
            return;
        }
    } else if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
    }

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f diff = sub_71005D9330(mActor);
    diff -= pos;
    diff.y = 0;
    const f32 dist = diff.length();
    const f32 range = sub_71007320F0(mActor, *mWeaponIdx_s) + (*mBaseDist_s + *mOutDist_s);
    changeToWait();
    if (dist >= range)
        setFailed();
}

bool MoriblinUnarmedBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MoriblinUnarmedBattle::leave_() {
    sub_71005DA114(mActor, &_90);
}

void MoriblinUnarmedBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

void MoriblinUnarmedBattle::changeToAttack() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("攻撃", &pack);
}

void MoriblinUnarmedBattle::changeToWait() {
    sub_71005DA114(mActor, &_90);
    _80 = ksys::Timer(10.0f, 10.0f);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
