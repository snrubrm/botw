#include "Game/AI/AI/aiSiteBossLswordRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Source namespace and helper ownership are unknown; declarations only.
bool sub_71002D1F2C(uking::act::SiteBoss* boss);
void sub_71002D36C8(uking::act::Enemy* enemy, const sead::SafeString& part_name);

namespace uking::ai {

namespace {
// inline-only in the original; name is a guess (repeated four times in the destructor)
void deletePartsActor(act::Enemy* enemy, const char* name) {
    if (enemy->getActorPartsActor(name).hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}
}  // namespace

SiteBossLswordRoot::SiteBossLswordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossLswordRoot::~SiteBossLswordRoot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        deletePartsActor(enemy, "WearFlame");
        deletePartsActor(enemy, "DrawingFlame");
        deletePartsActor(enemy, "SiteBossBigFlameBall0");
        deletePartsActor(enemy, "SiteBossBigFlameBall1");
        enemy->sub_7100D3CFEC("WearFlame");
        enemy->sub_7100D3CFEC("DrawingFlame");
        enemy->sub_7100D3CFEC("SiteBossBigFlameBall0");
        enemy->sub_7100D3CFEC("SiteBossBigFlameBall1");
    }
}

bool SiteBossLswordRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossLswordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
    if (!_160)
        _160 = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "TgBarrier");
    if (checkHpRate(mActor, 0.5f))
        changeAS("Chemical_Loop", true, 3, 0);
    else
        changeAS("Blade_Blue", true, 3, 0);
}

void SiteBossLswordRoot::calc_() {
    SiteBossRoot::calc_();
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || !_160)
        return;

    if (act::SiteBoss::sub_71002D3804(boss, "WearFlame")) {
        if (!_160->isAddedToWorld())
            _160->addToWorld();
    } else if (_160->isAddedToWorld()) {
        _160->removeFromWorld();
    }
}

void SiteBossLswordRoot::leave_() {
    SiteBossRoot::leave_();
    if (!isActorGoingBackToRootAi())
        return;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (auto* part : enemy->_1128.mList) {
            auto& link = part->mLink;
            if (!link.hasProcInCalcState())
                continue;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.hasTag(0u))
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
}

void SiteBossLswordRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mFireBallAttackPower_s, "FireBallAttackPower");
    getStaticParam(&mFireBallMinDamage_s, "FireBallMinDamage");
    getStaticParam(&mBigFireBallAttackPower_s, "BigFireBallAttackPower");
    getStaticParam(&mBigFireBallMinDamage_s, "BigFireBallMinDamage");
    getStaticParam(&mWearFlameAttackPower_s, "WearFlameAttackPower");
    getStaticParam(&mWearFlameMinDamage_s, "WearFlameMinDamage");
    getStaticParam(&mBigFireBallScaleTime0_s, "BigFireBallScaleTime0");
    getStaticParam(&mBigFireBallScaleMax_s, "BigFireBallScaleMax");
    getStaticParam(&mBigFireBallScaleTime1_s, "BigFireBallScaleTime1");
    getStaticParam(&mBigFireBallMoveSpeed0_s, "BigFireBallMoveSpeed0");
    getStaticParam(&mBigFireBallMoveSpeed1_s, "BigFireBallMoveSpeed1");
    getStaticParam(&mBigFireBallPosOffset_s, "BigFireBallPosOffset");
    getStaticParam(&mBigFireBallRotOffset_s, "BigFireBallRotOffset");
}

void SiteBossLswordRoot::m34(act::SiteBoss* boss) {
    SiteBossRoot::m34(boss);
    if (boss && sub_71002D1F2C(boss)) {
        sub_71002D36C8(boss, "WearFlame");
        act::SiteBoss::sub_71002D3498(boss, mActor);
    }
}

// NON_MATCHING: the original tests the range as `type - 9 > 5` (cmp #5; b.hi), the switch gives
// cmp #6; b.hs and an if-statement range check is turned into a select
bool SiteBossLswordRoot::m35(act::SiteBoss* boss) {
    const bool ret = SiteBossRoot::m35(boss);
    if (!boss)
        return ret;

    if (!getCurrentChild())
        return false;

    if (auto* damage_mgr = sub_710072BA90(mActor)) {
        switch (damage_mgr->getField54()) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            return false;
        default:
            break;
        }
    }
    return ret;
}

}  // namespace uking::ai
