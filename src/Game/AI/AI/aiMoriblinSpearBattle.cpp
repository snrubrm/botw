#include "Game/AI/AI/aiMoriblinSpearBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

MoriblinSpearBattle::MoriblinSpearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinSpearBattle::~MoriblinSpearBattle() = default;

// NON_MATCHING: clang inlines changeToShortRange/sub_71004AA888 here; the original tail-calls them
void MoriblinSpearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sead::Vector3f diff = sub_71005D9330(mActor);
        diff -= mActor->getMtx().getTranslation();
        diff.y = 0;
        if (diff.length() <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s) {
            changeToShortRange();
            return;
        }
    }
    sub_71004AA888();
}

bool MoriblinSpearBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MoriblinSpearBattle::leave_() {
    sub_71005DA114(mActor, &_90);
}

void MoriblinSpearBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mForceAttackDist_s, "ForceAttackDist");
}

void MoriblinSpearBattle::changeToShortRange() {
    setDamageCallbackTiming(mActor, 4, &_90);
    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("近距離", &params);
}

void MoriblinSpearBattle::sub_71004AA888() {
    sead::Vector3f diff = sub_71005D9330(mActor);
    diff -= mActor->getMtx().getTranslation();
    diff.y = 0;
    if (diff.length() >= sub_71007320F0(mActor, *mWeaponIdx_s) + (*mBaseDist_s + *mOutDist_s))
        setFailed();
    changeToWait();
}

void MoriblinSpearBattle::changeToWait() {
    sub_71005DA114(mActor, &_90);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
    _80 = ksys::Timer(10, 10);

    sead::Vector3f pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void MoriblinSpearBattle::changeToForcedSmallAttack() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("強制小攻撃", &pack);
}

void MoriblinSpearBattle::changeToMidRange() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("中距離", &pack);
}

}  // namespace uking::ai
