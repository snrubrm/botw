#include "Game/AI/AI/aiMoriblinUnarmedBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

void MoriblinUnarmedBattle::sub_71004ACE74() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("攻撃", &pack);
}

}  // namespace uking::ai
