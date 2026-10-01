#include "Game/AI/AI/aiEnemyFeintBattle.h"

namespace uking::ai {

EnemyFeintBattle::EnemyFeintBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyFeintBattle::~EnemyFeintBattle() = default;

void EnemyFeintBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mIsAttackEnd_s, "IsAttackEnd");
}

bool EnemyFeintBattle::isFinished() const {
    if (*mIsAttackEnd_s && getCurrentChild()->isFinished() && isCurrentChild("戦闘攻撃"))
        return true;
    return ActionBase::isFinished();
}

bool EnemyFeintBattle::isFailed() const {
    if (*mIsAttackEnd_s && getCurrentChild()->isFailed() && isCurrentChild("戦闘攻撃"))
        return true;
    return ActionBase::isFailed();
}

}  // namespace uking::ai
