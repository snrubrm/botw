#include "Game/AI/Action/actionBackStep.h"

namespace uking::action {

BackStep::BackStep(const InitArg& arg) : BackStepBase(arg) {}

void BackStep::m34() {
    playAS("BackStepStart", false, 0, 0, -1.0f);
}

void BackStep::m35() {
    playAS("BackStep", false, 0, 0, -1.0f);
}

void BackStep::m36() {
    playAS("BackStepPreLand", false, 0, 0, -1.0f);
}

void BackStep::m37() {
    playAS("BackStepEnd", false, 0, 0, -1.0f);
}

}  // namespace uking::action
