#include "Game/AI/AI/aiTargetStateSelect.h"

namespace uking::ai {

TargetStateSelect::TargetStateSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetStateSelect::~TargetStateSelect() = default;

bool TargetStateSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetStateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetStateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetStateSelect::loadParams_() {}

bool TargetStateSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetStateSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool TargetStateSelect::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
