#include "Game/AI/AI/aiEnemyPursuingAttackCheck.h"

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

}  // namespace uking::ai
