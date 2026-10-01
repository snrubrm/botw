#include "Game/AI/AI/aiCliffCheckSelect.h"

namespace uking::ai {

CliffCheckSelect::CliffCheckSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CliffCheckSelect::~CliffCheckSelect() = default;

void CliffCheckSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710035116C())
        changeChild("崖である", params);
    else
        changeChild("崖でない", params);
}

bool CliffCheckSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool CliffCheckSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool CliffCheckSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void CliffCheckSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckAngle_s, "CheckAngle");
    getStaticParam(&mIsSelectFirstTime_s, "IsSelectFirstTime");
}

// NON_MATCHING: the original materialises the finished-or-failed result as a bool before re-fetching the child
void CliffCheckSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (!getCurrentChild()->isChangeable() || *mIsSelectFirstTime_s)
        return;

    if (isCurrentChild("崖である")) {
        if (!sub_710035116C())
            changeChild("崖でない");
    } else if (isCurrentChild("崖でない")) {
        if (sub_710035116C())
            changeChild("崖である");
    }
}

}  // namespace uking::ai
