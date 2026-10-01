#include "Game/AI/AI/aiTargetDirLRSelect.h"

namespace uking::ai {

TargetDirLRSelect::TargetDirLRSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetDirLRSelect::~TargetDirLRSelect() = default;

void TargetDirLRSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (m34()) {
    case 0:
        changeChild("左側", params);
        break;
    case 1:
        changeChild("右側", params);
        break;
    default:
        changeChild("左側", params);
        setFailed();
        break;
    }
}

void TargetDirLRSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else
        setFailed();
}

}  // namespace uking::ai
