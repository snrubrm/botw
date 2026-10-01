#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

// NON_MATCHING: instruction scheduling / register allocation around the second sender (_198)
EnemyRoot::EnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoot::~EnemyRoot() = default;

bool EnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRoot::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getStaticParam(&mIgnoreHell_s, "IgnoreHell");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
    getMapUnitParam(&mEquipItem3_m, "EquipItem3");
    getMapUnitParam(&mEquipItem4_m, "EquipItem4");
    getMapUnitParam(&mRideHorseName_m, "RideHorseName");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mForceSealSilentKillCount_a, "ForceSealSilentKillCount");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void EnemyRoot::m37() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("リアクション");
}

void EnemyRoot::m40() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("所持");
}

void EnemyRoot::m42() {
    _1c8 = false;
    changeChild("奈落");
}

void EnemyRoot::m35() {
    sub_71005D6E28(mActor);
}

}  // namespace uking::ai
