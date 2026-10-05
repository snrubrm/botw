#include "Game/AI/AI/aiEnemyPursuingArrowBattle.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyPursuingArrowBattle::EnemyPursuingArrowBattle(const InitArg& arg) : BokoblinArrowBattle(arg) {}

EnemyPursuingArrowBattle::~EnemyPursuingArrowBattle() = default;

void EnemyPursuingArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BokoblinArrowBattle::enter_(params);
}

// NON_MATCHING: Vector difference component loads and arithmetic scheduling differ.
void EnemyPursuingArrowBattle::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("追撃ち")) {
        changeToWait();
        return;
    }
    if (getCurrentChild()->isChangeable() && isCurrentChild("待機")) {
        auto* actor = mActor;
        if (actor && _148.value <= sead::Mathf::epsilon() && sub_710072E1B4(actor, false) &&
            !((_11c - *mParams.mTargetPos_d).length() > 5.0f) &&
            sub_71005DFBE4(static_cast<act::Enemy*>(actor), *mPursuingAttackStartDist_s,
                          *mPursuingAttackStartAng_s)) {
            changeToFollowUp();
            return;
        }
    }
    BokoblinArrowBattle::calc_();
    if (isCurrentChild("待機") && !(_148.value <= sead::Mathf::epsilon()))
        _148.update();
}

void EnemyPursuingArrowBattle::loadParams_() {
    BokoblinArrowBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartDist_s, "PursuingAttackStartDist");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

void EnemyPursuingArrowBattle::changeToFollowUp() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    const s32 time = s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand));
    _148 = ksys::Timer(time, time);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_11c, "TargetPos", -1);
    changeChild("追撃ち", &pack);
}

}  // namespace uking::ai
