#include "Game/AI/AI/aiBocoblinBackStepAttack.h"

namespace uking::ai {

BocoblinBackStepAttack::BocoblinBackStepAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BocoblinBackStepAttack::~BocoblinBackStepAttack() = default;

void BocoblinBackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool BocoblinBackStepAttack::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool BocoblinBackStepAttack::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void BocoblinBackStepAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAttackPer_d, "AttackPer");
}

}  // namespace uking::ai
