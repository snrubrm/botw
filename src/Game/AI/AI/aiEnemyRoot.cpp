#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

// NON_MATCHING: instruction scheduling / register allocation around the second sender (_198)
EnemyRoot::EnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoot::~EnemyRoot() {
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
}

bool EnemyRoot::init_(sead::Heap* heap) {
    const float* fall_height{};
    getStaticParam(&fall_height, "FallHeight");
    if (*fall_height >= 0.0f) {
        _38 = new (heap) Unk_7100702370(mActor, fall_height);
        if (!_38)
            return false;
    }
    return true;
}

void EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_38)
        _38->sub_7100702370();
    *mIsTrgChangeUnderWaterState_a = false;
    m34(params);
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

void EnemyRoot::m39() {
    if (isCurrentChild("通常"))
        *mIsTrgChangeUnderWaterState_a = true;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.resetBit(13);
    changeChild("水中");
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

bool EnemyRoot::m35() {
    return sub_71005D6E28(mActor);
}

}  // namespace uking::ai
