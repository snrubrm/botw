#include "Game/AI/AI/aiGuardFrequencySelect.h"

namespace uking::ai {

GuardFrequencySelect::GuardFrequencySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardFrequencySelect::~GuardFrequencySelect() = default;

void GuardFrequencySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710040CA40())
        changeChild("ガード", params);
    else
        changeChild("通常", params);
}

void GuardFrequencySelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else
        setFailed();
}

void GuardFrequencySelect::loadParams_() {}

}  // namespace uking::ai
