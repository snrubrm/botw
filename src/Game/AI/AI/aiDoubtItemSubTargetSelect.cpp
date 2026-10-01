#include "Game/AI/AI/aiDoubtItemSubTargetSelect.h"

namespace uking::ai {

DoubtItemSubTargetSelect::DoubtItemSubTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoubtItemSubTargetSelect::~DoubtItemSubTargetSelect() = default;

bool DoubtItemSubTargetSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DoubtItemSubTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoubtItemSubTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DoubtItemSubTargetSelect::calc_() {}

void DoubtItemSubTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoubtItemSubTargetSelect::loadParams_() {}

bool DoubtItemSubTargetSelect::m34() {
    return getCurrentChild()->isFailed();
}

}  // namespace uking::ai
