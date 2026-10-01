#include "Game/AI/AI/aiEnemyTargetInSightSelect.h"

namespace uking::ai {

EnemyTargetInSightSelect::EnemyTargetInSightSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyTargetInSightSelect::~EnemyTargetInSightSelect() = default;

bool EnemyTargetInSightSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyTargetInSightSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnemyTargetInSightSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyTargetInSightSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTargetInSightSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void EnemyTargetInSightSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
