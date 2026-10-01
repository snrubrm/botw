#include "Game/AI/AI/aiForkActionAndJoin.h"

namespace uking::ai {

ForkActionAndJoin::ForkActionAndJoin(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForkActionAndJoin::~ForkActionAndJoin() = default;

bool ForkActionAndJoin::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForkActionAndJoin::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
    changeChild("行動", params);
}

void ForkActionAndJoin::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForkActionAndJoin::loadParams_() {}

bool ForkActionAndJoin::isFinished() const {
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFinished();
    return _38 == 0;
}

bool ForkActionAndJoin::isFailed() const {
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFailed();
    return _38 == 1;
}

}  // namespace uking::ai
