#include "Game/AI/Action/actionWindCutter.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

WindCutter::WindCutter(const InitArg& arg) : ChemicalAttack(arg) {}

WindCutter::~WindCutter() = default;

bool WindCutter::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void WindCutter::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void WindCutter::leave_() {
    ChemicalAttack::leave_();
}

void WindCutter::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mLevelAtkMult_s, "LevelAtkMult");
    getStaticParam(&mLevelBaseScaleAdd_s, "LevelBaseScaleAdd");
    getStaticParam(&mLevelRangeMult_s, "LevelRangeMult");
    getStaticParam(&mLevelScaleMult_s, "LevelScaleMult");
    getStaticParam(&mIsLevelOneScaleOne_s, "IsLevelOneScaleOne");
    getMapUnitParam(&mAttackLevel_m, "AttackLevel");
    getMapUnitParam(&mAttackDirType_m, "AttackDirType");
    getAITreeVariable(&mAttackAttrEventKill_a, "AttackAttrEventKill");
}

void WindCutter::calc_() {
    ChemicalAttack::calc_();
}

int WindCutter::m35() {
    return 1;
}

f32 WindCutter::m34() {
    return ChemicalAttack::m34() * sead::Mathi::max(*mAttackLevel_m, 0) * *mLevelRangeMult_s;
}

int WindCutter::m36() {
    int result = ChemicalAttack::m36();
    if (*mAttackAttrEventKill_a)
        result |= 0x40000000;
    return result;
}

int WindCutter::m37() {
    return *mAttackPower_m * sead::Mathi::max(*mAttackLevel_m, 0) * *mLevelAtkMult_s;
}

bool WindCutter::m33() {
    if (ChemicalAttack::m33())
        return true;
    auto* actor = mActor;
    return isLandedMaybe(actor, false) || isBgGroundHit(actor, false) ||
           sub_71007A4178(actor, false);
}

}  // namespace uking::action
