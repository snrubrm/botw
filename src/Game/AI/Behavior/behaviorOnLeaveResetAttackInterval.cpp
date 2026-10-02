#include "Game/AI/Behavior/behaviorOnLeaveResetAttackInterval.h"

namespace uking::behavior {

OnLeaveResetAttackInterval::OnLeaveResetAttackInterval(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

OnLeaveResetAttackInterval::~OnLeaveResetAttackInterval() = default;

bool OnLeaveResetAttackInterval::m6(sead::Heap* heap) {
    return true;
}

void OnLeaveResetAttackInterval::m7() {}

void OnLeaveResetAttackInterval::m8() {}

void OnLeaveResetAttackInterval::loadParams() {

}

}  // namespace uking::behavior
