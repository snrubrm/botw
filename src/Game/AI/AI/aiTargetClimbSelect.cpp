#include "Game/AI/AI/aiTargetClimbSelect.h"

namespace uking::ai {

TargetClimbSelect::TargetClimbSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetClimbSelect::~TargetClimbSelect() = default;

bool TargetClimbSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetClimbSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetClimbSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetClimbSelect::loadParams_() {}

bool TargetClimbSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetClimbSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

}  // namespace uking::ai
