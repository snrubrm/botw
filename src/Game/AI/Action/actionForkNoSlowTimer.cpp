#include "Game/AI/Action/actionForkNoSlowTimer.h"
#include "Game/AI/aiNoSlowTime.h"

namespace uking::action {

ForkNoSlowTimer::ForkNoSlowTimer(const InitArg& arg) : ForkTimer(arg) {}

ForkNoSlowTimer::~ForkNoSlowTimer() = default;

bool ForkNoSlowTimer::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void ForkNoSlowTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void ForkNoSlowTimer::leave_() {
    ForkTimer::leave_();
}

void ForkNoSlowTimer::loadParams_() {
    ForkTimer::loadParams_();
}

void ForkNoSlowTimer::calc_() {
    ForkTimer::calc_();
}

// NON_MATCHING: the original keeps the default ratio 1.0f in d8 across the isSlowTimeMaybe() call (fmov s8, #1.0
// before the call); ours materialises it after
float ForkNoSlowTimer::m33() {
    return getNoSlowTimeRatio();
}

}  // namespace uking::action
