#include "Game/AI/AI/aiLandHumEnemyUnarmedBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

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

void LandHumEnemyUnarmedBattle::changeToFindItem() {
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    mActor->m45()->sub_7100F7D350();
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_118, "ShootItem", -1);
    pack.addVec3(sub_71005D98D8(mActor), "TargetPos", -1);
    changeChild("アイテム発見", &pack);
}

void LandHumEnemyUnarmedBattle::changeToAvoidDanger() {
    if (_138.hasProcInCalcState()) {
        ksys::act::ai::InlineParamPack pack;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_138, &accessor);
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        pack.addVec3(pos, "TargetPos", -1);
        pack.addActor(_138, "TargetActor", -1);
        changeChild("危険回避", &pack);
    }
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

// NON_MATCHING: same operations; the scheduling of the offset products / the matrix product loads differs (the original
// loads the offset vector pair first and adds the translation after all three dot products)
bool LandHumEnemyUnarmedBattle::sub_7100470D54(ksys::act::BaseProcLink* link, bool a2) {
    auto* actor = mActor;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (!accessor.isAttClientEnabled("Grab"))
        return false;
    ksys::res::AttCheck_Unk1 arg;
    arg._0 = actor->getMtx();
    const auto& base_offset = *mParams.mAttOffset_s;
    const auto& scale = actor->getScale();
    const sead::Vector3f offset(base_offset.x * scale.x, base_offset.y * scale.y,
                                base_offset.z * scale.z);
    sead::Vector3f position;
    position.setMul(actor->getMtx(), offset);
    arg._0.setTranslation(position);
    arg._36 = a2;
    arg._35 = true;
    arg._34 = *mParams.mCanGrabHeavy_s;
    arg._30 = *mParams.mGrabCheckRadius_s;
    return accessor.sub_7100D13AE4("Grab", actor, &arg, false);
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

void LandHumEnemyUnarmedBattle::m35(const sead::Vector3f& target) {
    sub_710046FC10();
    UnarmedEnemySearch::m35(target);
}

void LandHumEnemyUnarmedBattle::m42() {
    _799 = false;
    changeToBattle();
}

void LandHumEnemyUnarmedBattle::changeToBattle() {
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D98D8(mActor), "TargetPos", -1);
    changeChild("戦闘", &pack);
}

// The getName() call and the profile comparison results are unused in the original (their use was
// compiled out); the calls remain.
// NON_MATCHING: scheduling only (loop setup order and the fcsel of min_dist).
const ksys::act::BaseProcLink* LandHumEnemyUnarmedBattle::sub_7100471E98() {
    const ksys::act::BaseProcLink* nearest = nullptr;
    if (auto* nav = mActor->m45()) {
        const sead::Vector3f nav_pos = nav->_194;
        f32 min_dist = sead::Mathf::maxNumber();
        for (auto& entry : _150) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry._0.mLink, &accessor);
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            accessor.getName();
            const f32 dist = (nav_pos - pos).length();
            if (dist <= min_dist) {
                nearest = &entry._0.mLink;
                min_dist = dist;
            }
            const bool is_shield = accessor.getProfile() == "WeaponShield";
            static_cast<void>(is_shield);
        }
    }
    if (!nearest)
        nearest = &ksys::act::getDummyBaseProcLink();
    return nearest;
}

bool LandHumEnemyUnarmedBattle::sub_7100472020(const ksys::act::BaseProcLink* link) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return true;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f target;
    accessor.getActorMtx().getTranslation(target);
    const sead::Vector3f self = enemy->getMtx().getTranslation();
    return enemy->sub_710001A204(target, self, sub_71005D9330(mActor),
                                 *mParams.mSearchWeaponTargetDist_s);
}

}  // namespace uking::ai
