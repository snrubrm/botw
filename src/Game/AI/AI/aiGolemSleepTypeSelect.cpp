#include "Game/AI/AI/aiGolemSleepTypeSelect.h"

namespace uking::ai {

GolemSleepTypeSelect::GolemSleepTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
GolemSleepTypeSelect::~GolemSleepTypeSelect() {
    ;
}

bool GolemSleepTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemSleepTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemSleepTypeSelect::calc_() {}

bool GolemSleepTypeSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool GolemSleepTypeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void GolemSleepTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemSleepTypeSelect::loadParams_() {
    getMapUnitParam(&mGolemSleepType_m, "GolemSleepType");
}

}  // namespace uking::ai
