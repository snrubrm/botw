#include "Game/AI/Action/actionWindCutter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

WindCutter::WindCutter(const InitArg& arg) : ChemicalAttack(arg) {}

WindCutter::~WindCutter() = default;

bool WindCutter::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

// NON_MATCHING: operand order of two commutative fmuls (level * ScaleMult and scale.z * mult).
void WindCutter::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_level_one_scale_one = *mIsLevelOneScaleOne_s;
    const int level = *mAttackLevel_m;
    auto* actor = mActor;
    if (!is_level_one_scale_one || level >= 2) {
        const f32 mult = f32(*mLevelBaseScaleAdd_s) + f32(level > 0 ? level : 0) * *mLevelScaleMult_s;
        sead::Vector3f scale = actor->getScale();
        scale *= mult;
        actor->setScale(scale);
    }
    ChemicalAttack::enter_(params);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor))
        bullet->_cf4 |= 1;
    _c0 = true;
}

void WindCutter::leave_() {
    ChemicalAttack::leave_();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        bullet->_cf4 &= ~1;
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

int WindCutter::m39() {
    if (sead::DynamicCast<ksys::act::Bullet>(mActor))
        return *mAttackDirType_m;
    return ChemicalAttack::m39();
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
