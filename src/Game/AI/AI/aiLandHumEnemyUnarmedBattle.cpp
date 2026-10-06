#include "Game/AI/AI/aiLandHumEnemyUnarmedBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

// NON_MATCHING: scheduling / register allocation of the inlined FixedObjList setup stores (same as
// UnarmedEnemyNoiseTarget's ctor)
LandHumEnemyUnarmedBattle::LandHumEnemyUnarmedBattle(const InitArg& arg)
    : UnarmedEnemySearch(arg) {}

LandHumEnemyUnarmedBattle::~LandHumEnemyUnarmedBattle() = default;

void LandHumEnemyUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    _150.clear();
    _148 = -1;
    _798 = sub_7100726E54(mActor);
    _799 = true;
    UnarmedEnemySearch::enter_(params);
}

void LandHumEnemyUnarmedBattle::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mParams.mEquipItemSearchIdx_s));
        enemy->sub_7100019D38(_118);
        enemy->sub_7100019D38(_108);
    }
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    _150.clear();
}

void LandHumEnemyUnarmedBattle::sub_71004703E8() {
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019D38(_118);
    _118.reset();
}

bool LandHumEnemyUnarmedBattle::sub_7100470ED4(ksys::act::BaseProcLink& link) const {
    auto* actor = mActor;
    if (sub_7100739030(actor, link))
        return true;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    sead::Vector3f self;
    actor->getMtx().getTranslation(self);
    const f32 reach = getReachDistanceMaybe();
    return (pos - self).squaredLength() < reach * reach;
}

void LandHumEnemyUnarmedBattle::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mParams.mLostTimer_s, "LostTimer");
    getStaticParam(&mParams.mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mParams.mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mParams.mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mParams.mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getStaticParam(&mParams.mSearchBowTargetDist_s, "SearchBowTargetDist");
    getStaticParam(&mParams.mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mParams.mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mParams.mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mParams.mAttOffset_s, "AttOffset");
    getStaticParam(&mParams.mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    getStaticParam(&mParams.mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mParams.mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mParams.mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mLostVMin_s, "LostVMin");
    getStaticParam(&mParams.mLostVMax_s, "LostVMax");
    getStaticParam(&mParams.mLostRange_s, "LostRange");
    getStaticParam(&mParams.mOnCoHitAllowGrabAngle_s, "OnCoHitAllowGrabAngle");
}

}  // namespace uking::ai
