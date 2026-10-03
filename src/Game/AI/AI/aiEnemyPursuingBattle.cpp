#include "Game/AI/AI/aiEnemyPursuingBattle.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyPursuingBattle::EnemyPursuingBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyPursuingBattle::~EnemyPursuingBattle() = default;

void EnemyPursuingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyPursuingBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("追撃ち攻撃")) {
            sub_7100381ED4();
            m37();
            return;
        }
    }

    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("戦闘準備") && sub_71003A9AE8()) {
            changeToFollowUpAttack();
            return;
        }
    }

    EnemyBattle::calc_();
    if (isCurrentChild("戦闘準備") && !(_a8.value <= sead::Mathf::epsilon()))
        _a8.update();
}

void EnemyPursuingBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

void EnemyPursuingBattle::changeToFollowUpAttack() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    _a8.reset(s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand)));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追撃ち攻撃", &pack);
}

}  // namespace uking::ai
