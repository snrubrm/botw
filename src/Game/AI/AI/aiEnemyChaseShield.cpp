#include "Game/AI/AI/aiEnemyChaseShield.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyChaseShield::EnemyChaseShield(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChaseShield::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyChaseShield::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChaseShield::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mTurnAng_s, "TurnAng");
    getStaticParam(&mShieldReachDist_s, "ShieldReachDist");
}

void EnemyChaseShield::changeToRotate() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    } else {
        pos = sub_71005D9330(mActor);
    }

    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

void EnemyChaseShield::sub_7100384290() {
    if (_58)
        _58->_8 = -1;

    auto* link = mTargetWeapon_d;
    sead::Vector3f pos;
    if (link && link->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    } else {
        pos = sub_71005D9330(mActor);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ナビ追跡", &pack);
}

void EnemyChaseShield::changeToAcquire() {
    ksys::act::ai::InlineParamPack pack;
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        sead::Vector3f pos;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
        pack.addVec3(pos, "TargetPos", -1);
        pack.addActor(*mTargetWeapon_d, "TargetWeapon", -1);
    } else {
        pack.addVec3(sead::Vector3f::zero, "TargetPos", -1);
        pack.addActor(ksys::act::getDummyBaseProcLink(), "TargetWeapon", -1);
    }
    changeChild("取得", &pack);
}

}  // namespace uking::ai
