#include "Game/AI/AI/aiEnemyPursuingAttackCheck.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyPursuingAttackCheck::EnemyPursuingAttackCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyPursuingAttackCheck::~EnemyPursuingAttackCheck() = default;

void EnemyPursuingAttackCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyPursuingAttackCheck::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyPursuingAttackCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyPursuingAttackCheck::loadParams_() {
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
    getStaticParam(&mAttackAng_s, "AttackAng");
}

bool EnemyPursuingAttackCheck::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("通常戦闘") && getCurrentChild()->isFinished());
}

bool EnemyPursuingAttackCheck::isFailed() const {
    return ActionBase::isFailed() || (isCurrentChild("通常戦闘") && getCurrentChild()->isFailed());
}

void EnemyPursuingAttackCheck::sub_71003A92AC() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    _58.reset(s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand)));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追撃ち攻撃", &pack);
}

}  // namespace uking::ai
