#include "Game/AI/Action/actionForkTimer.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

ForkTimer::ForkTimer(const InitArg& arg) : ForkTimerBase(arg) {}

ForkTimer::~ForkTimer() = default;

void ForkTimer::loadParams_() {
    ForkTimerBase::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
}

int ForkTimer::m32() {
    return *mWaitFrame_s + *mWaitFrameRand_s * sead::GlobalRandom::instance()->getF32();
}

}  // namespace uking::action
