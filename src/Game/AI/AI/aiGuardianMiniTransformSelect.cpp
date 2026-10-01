#include "Game/AI/AI/aiGuardianMiniTransformSelect.h"

namespace uking::ai {

GuardianMiniTransformSelect::GuardianMiniTransformSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniTransformSelect::~GuardianMiniTransformSelect() = default;

bool GuardianMiniTransformSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GuardianMiniTransformSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GuardianMiniTransformSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniTransformSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsTransformedGuardianMini_a)
        changeChild("変形後", params);
    else
        changeChild("変形前", params);
}

void GuardianMiniTransformSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else
        setFailed();
}

void GuardianMiniTransformSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniTransformSelect::loadParams_() {
    getAITreeVariable(&mIsTransformedGuardianMini_a, "IsTransformedGuardianMini");
}

}  // namespace uking::ai
