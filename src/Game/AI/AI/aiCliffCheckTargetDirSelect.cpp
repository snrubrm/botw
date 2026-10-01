#include "Game/AI/AI/aiCliffCheckTargetDirSelect.h"

namespace uking::ai {

CliffCheckTargetDirSelect::CliffCheckTargetDirSelect(const InitArg& arg) : CliffCheckSelect(arg) {}

CliffCheckTargetDirSelect::~CliffCheckTargetDirSelect() = default;

void CliffCheckTargetDirSelect::calc_() {
    CliffCheckSelect::calc_();
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void CliffCheckTargetDirSelect::loadParams_() {
    CliffCheckSelect::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
