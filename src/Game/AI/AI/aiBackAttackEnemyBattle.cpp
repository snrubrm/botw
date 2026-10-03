#include "Game/AI/AI/aiBackAttackEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::ai {

BackAttackEnemyBattle::BackAttackEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

BackAttackEnemyBattle::~BackAttackEnemyBattle() = default;

bool BackAttackEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void BackAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void BackAttackEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void BackAttackEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAttackAngle_s, "BackAttackAngle");
}

void BackAttackEnemyBattle::calc_() {
    if (!isCurrentChild("背面攻撃")) {
        EnemyBattle::calc_();
        return;
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        return;
    }

    sub_71005DA114(mActor, &_98);
    if (child->isFailed()) {
        setFailed();
    } else {
        sub_7100381ED4();
        m37();
    }
}

void BackAttackEnemyBattle::changeToBackAttack() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("背面攻撃", &pack);
    setDamageCallbackTiming(mActor, 4, &_98);
}

}  // namespace uking::ai
