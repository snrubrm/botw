#include "Game/AI/AI/aiGuardianMiniRangeKeepMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

GuardianMiniRangeKeepMove::GuardianMiniRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

GuardianMiniRangeKeepMove::~GuardianMiniRangeKeepMove() = default;

void GuardianMiniRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void GuardianMiniRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void GuardianMiniRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
}

void GuardianMiniRangeKeepMove::calc_() {
    if (getCurrentChild()->isFailed() && isCurrentChild("戦闘歩行")) {
        setFailed();
        return;
    }
    if (getCurrentChild()->isChangeable() && isCurrentChild("戦闘歩行") && sub_71003AD1F8() &&
        sub_71003AD160()) {
        sub_71003ABF50();
        return;
    }
    EnemyRangeKeepMove::calc_();
}

}  // namespace uking::ai
