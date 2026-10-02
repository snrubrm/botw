#include "Game/AI/AI/aiSiteBossLswordRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

SiteBossLswordRoot::SiteBossLswordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossLswordRoot::~SiteBossLswordRoot() = default;

bool SiteBossLswordRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossLswordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
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
