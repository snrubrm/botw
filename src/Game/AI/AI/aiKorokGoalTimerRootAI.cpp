#include "Game/AI/AI/aiKorokGoalTimerRootAI.h"

namespace uking::ai {

// NON_MATCHING: the initial word and byte flag stores are scheduled in a different order.
KorokGoalTimerRootAI::KorokGoalTimerRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokGoalTimerRootAI::~KorokGoalTimerRootAI() = default;

bool KorokGoalTimerRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokGoalTimerRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokGoalTimerRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokGoalTimerRootAI::loadParams_() {
    getMapUnitParam(&mGoalCountLimit_m, "GoalCountLimit");
}

}  // namespace uking::ai
