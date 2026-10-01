#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyBaseArrowAttack::EnemyBaseArrowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyBaseArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710037E11C();
}

void EnemyBaseArrowAttack::m37() {}

bool EnemyBaseArrowAttack::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (getCurrentChild()->isFinished() && isCurrentChild("攻撃"));
}

bool EnemyBaseArrowAttack::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyBaseArrowAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyBaseArrowAttack::m36() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void EnemyBaseArrowAttack::m34() {
    sead::Vector3f pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("リロード", &pack);
}

}  // namespace uking::ai
