#include "Game/AI/Action/actionDoubleAttack.h"

namespace uking::action {

DoubleAttack::DoubleAttack(const InitArg& arg) : StepDoubleAttack(arg) {}

DoubleAttack::~DoubleAttack() = default;

void DoubleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    StepDoubleAttack::enter_(params);
    playAS("DoubleAttackStay", false, 0, 0, -1.0f);
}

}  // namespace uking::action
