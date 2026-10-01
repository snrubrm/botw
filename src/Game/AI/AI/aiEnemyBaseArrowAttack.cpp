#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
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

// NON_MATCHING: two stores of the request struct are scheduled in a different order
void EnemyBaseArrowAttack::sub_710037E11C() {
    sub_71005D787C(mActor, *mWeaponIdx_s, uking::act::Unk_71002eda38(2));
    sead::Vector3f pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("準備", &pack);
}

void EnemyBaseArrowAttack::calc_() {
    m36();
    m37();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("リロード")) {
            m35();
            return;
        }
        if (isCurrentChild("攻撃")) {
            setFinished();
            return;
        }
    }

    if (isCurrentChild("準備") && getCurrentChild()->isChangeable() &&
        sub_71005D8324(mActor, *mWeaponIdx_s)) {
        m34();
    }
}

}  // namespace uking::ai
