#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

// NON_MATCHING: ours keeps &_1b8 in a callee-saved register across the param memset
LandHumEnemyFindPlayer::LandHumEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LandHumEnemyFindPlayer::~LandHumEnemyFindPlayer() = default;

void LandHumEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _1e0 = false;
    if (mActor->get68f().load() || sub_71005D91A0(mActor, *mNoBurnWaterDepth_s))
        _1d8 = 1.0f;
    else
        _1d8 = 0.0f;
    _1e1 = sub_71005DA5AC(mActor, m53());
    if (!sub_710046096C()) {
        EnemyBaseFindPlayer::enter_(params);
        return;
    }

    const bool is_enemy = ksys::act::isEnemyProfile(&_1c8);
    sub_710037E9A4();
    if (is_enemy)
        sub_7100460EE8();
    else
        sub_7100461020();
}

void LandHumEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
    dmg::DamageInfoMgr::instance()->get4f8().sub_71006720C8(mActor);
}

// NON_MATCHING: the original keeps &mThrowWeaponPer_s in a callee-saved register from the start
void LandHumEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getStaticParam(&mChemicalSearchDist_s, "ChemicalSearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mChemicalActionDist_s, "ChemicalActionDist");
    getStaticParam(&mThrowWeaponPer_s, "ThrowWeaponPer");
    getStaticParam(&mThrowWeaponDist_s, "ThrowWeaponDist");
    getStaticParam(&mNoChemSearchWpIdx_s, "NoChemSearchWpIdx");
    getStaticParam(&mNoBurnWaterDepth_s, "NoBurnWaterDepth");
    getStaticParam(&mNearScaffoldDist_s, "NearScaffoldDist");
    getStaticParam(&mClimbVmin_s, "ClimbVmin");
    getStaticParam(&mClimbVmax_s, "ClimbVmax");
    getStaticParam(&mClimbHmax_s, "ClimbHmax");
}

bool LandHumEnemyFindPlayer::m43() {
    if (*mNearScaffoldDist_s > 0.0f && sub_71005D9744(mActor) == 3)
        return false;
    return EnemyBaseFindPlayer::m43();
}

}  // namespace uking::ai
