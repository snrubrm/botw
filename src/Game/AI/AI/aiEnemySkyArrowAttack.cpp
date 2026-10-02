#include "Game/AI/AI/aiEnemySkyArrowAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemySkyArrowAttack::EnemySkyArrowAttack(const InitArg& arg) : EnemyBaseArrowAttack(arg) {}

EnemySkyArrowAttack::~EnemySkyArrowAttack() = default;

bool EnemySkyArrowAttack::init_(sead::Heap* heap) {
    return EnemyBaseArrowAttack::init_(heap);
}

void EnemySkyArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseArrowAttack::enter_(params);
}

void EnemySkyArrowAttack::calc_() {
    EnemyBaseArrowAttack::calc_();
}

void EnemySkyArrowAttack::leave_() {
    EnemyBaseArrowAttack::leave_();
}

void EnemySkyArrowAttack::loadParams_() {
    EnemyBaseArrowAttack::loadParams_();
}

void EnemySkyArrowAttack::m34() {
    EnemyBaseArrowAttack::m34();
}

void EnemySkyArrowAttack::m35() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const s32 time = enemy->_f28.sub_7100001AA4(*mIntervalIntensity_s);
        enemy->_e68 = ksys::Timer(time, time);
    }

    sead::Vector3f pos = *mTargetPos_d;
    pos.y += 100.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addActor(sub_71005D94AC(mActor), "TargetActor", -1);
    changeChild("攻撃", &pack);
}

}  // namespace uking::ai
