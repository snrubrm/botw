#include "Game/AI/AI/aiEnemyPermitAttackSelect.h"

namespace uking::ai {

EnemyPermitAttackSelect::EnemyPermitAttackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyPermitAttackSelect::~EnemyPermitAttackSelect() = default;

bool EnemyPermitAttackSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyPermitAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyPermitAttackSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyPermitAttackSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyPermitAttackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyPermitAttackSelect::loadParams_() {
    getStaticParam(&mIsIgnoreEnemyMgr_s, "IsIgnoreEnemyMgr");
}

}  // namespace uking::ai
