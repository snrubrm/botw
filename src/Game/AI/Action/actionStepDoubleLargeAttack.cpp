#include "Game/AI/Action/actionStepDoubleLargeAttack.h"

namespace uking::action {

StepDoubleLargeAttack::StepDoubleLargeAttack(const InitArg& arg) : StepDoubleAttack(arg) {}

int StepDoubleLargeAttack::m32() {
    return 2;
}

}  // namespace uking::action
