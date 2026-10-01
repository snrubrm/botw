#include "Game/AI/AI/aiCliffCheckSelect.h"

namespace uking::ai {

CliffCheckSelect::CliffCheckSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CliffCheckSelect::~CliffCheckSelect() = default;

void CliffCheckSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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

}  // namespace uking::ai
