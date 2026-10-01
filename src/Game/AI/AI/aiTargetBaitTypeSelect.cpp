#include "Game/AI/AI/aiTargetBaitTypeSelect.h"

namespace uking::ai {

TargetBaitTypeSelect::TargetBaitTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetBaitTypeSelect::~TargetBaitTypeSelect() = default;

void TargetBaitTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005BC0B4(params);
}

void TargetBaitTypeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void TargetBaitTypeSelect::loadParams_() {
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
}

}  // namespace uking::ai
