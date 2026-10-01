#include "Game/AI/AI/aiCountSelect.h"

namespace uking::ai {

CountSelect::CountSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CountSelect::~CountSelect() = default;

bool CountSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool CountSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool CountSelect::init_(sead::Heap* heap) {
    _40 = 0;
    return true;
}

void CountSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_40++ < *mCounter_s)
        changeChild("以前", params);
    else
        changeChild("以後", params);
}

void CountSelect::calc_() {}

void CountSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CountSelect::loadParams_() {
    getStaticParam(&mCounter_s, "Counter");
}

}  // namespace uking::ai
