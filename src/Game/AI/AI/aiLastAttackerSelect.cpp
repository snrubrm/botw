#include "Game/AI/AI/aiLastAttackerSelect.h"

namespace uking::ai {

LastAttackerSelect::LastAttackerSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastAttackerSelect::~LastAttackerSelect() = default;

bool LastAttackerSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LastAttackerSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool LastAttackerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastAttackerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastAttackerSelect::calc_() {}

void LastAttackerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastAttackerSelect::loadParams_() {}

}  // namespace uking::ai
