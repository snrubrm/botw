#include "Game/AI/AI/aiLynelRecognizeTarget.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LynelRecognizeTarget::LynelRecognizeTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRecognizeTarget::~LynelRecognizeTarget() = default;

bool LynelRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelRecognizeTarget::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    mActor->m93(0, 0.0f);
}

void LynelRecognizeTarget::loadParams_() {
    getStaticParam(&mAttensionStartPoint_s, "AttensionStartPoint");
    getStaticParam(&mObserveEndPoint_s, "ObserveEndPoint");
    getStaticParam(&mDrawnWeaponPoint_s, "DrawnWeaponPoint");
    getStaticParam(&mWeaponAimPoint_s, "WeaponAimPoint");
    getStaticParam(&mAttackPoint_s, "AttackPoint");
    getStaticParam(&mDashPoint_s, "DashPoint");
    getStaticParam(&mAppPoint_s, "AppPoint");
    getStaticParam(&mHorseRidePoint_s, "HorseRidePoint");
    getStaticParam(&mDamagePoint_s, "DamagePoint");
    getStaticParam(&mTrickedMaskPoint_s, "TrickedMaskPoint");
    getStaticParam(&mBombPoint_s, "BombPoint");
    getStaticParam(&mAimPoint_s, "AimPoint");
    getStaticParam(&mNearDistPoint_s, "NearDistPoint");
    getStaticParam(&mMiddleDistPoint_s, "MiddleDistPoint");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mTiredPoint_s, "TiredPoint");
    getStaticParam(&mForceBattleStartTime_s, "ForceBattleStartTime");
    getStaticParam(&mNearDistance_s, "NearDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mAimAngle_s, "AimAngle");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
}

void LynelRecognizeTarget::changeToReturn() {
    sead::Vector3f pos;
    mActor->getHomePos(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("帰還", &pack);
}

void LynelRecognizeTarget::changeToNotice() {
    _108 = 0;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);
}

void LynelRecognizeTarget::changeToAlert() {
    const f32 time = *mForceBattleStartTime_s;
    _108 = 0;
    _118 = time;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("警戒", &pack);
}

void LynelRecognizeTarget::changeToObserve() {
    const f32 time = *mForceBattleStartTime_s;
    _108 = 0;
    _118 = time;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("観察", &pack);
}

void LynelRecognizeTarget::changeToStartBattle() {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("戦闘開始", &pack);

    actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_e84.setBit(1);
}

void LynelRecognizeTarget::changeToForceStartBattle() {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("強制戦闘開始", &pack);

    actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_e84.setBit(1);
}

}  // namespace uking::ai
