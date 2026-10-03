#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/Action/actionForkLodNoCountTimer.h"

namespace uking::action {

// NON_MATCHING: regalloc only (x9 / x10 swapped for the actor pointer and the -1 constant).
ForkLodNoCountTimer::ForkLodNoCountTimer(const InitArg& arg) : Fork(arg) {}

ForkLodNoCountTimer::~ForkLodNoCountTimer() = default;

bool ForkLodNoCountTimer::init_(sead::Heap* heap) {
    if (!Fork::init_(heap))
        return false;
    _50 = !*mIsTrgStart_s;
    const int wait = *mWaitFrame_s;
    const int wait_max = *mWaitFrameRand_s + wait;
    _68 = sead::Mathi::min(wait, wait_max);
    _6c = sead::Mathi::max(wait, wait_max);
    _64 = *mCamDist_s;
    return true;
}

void ForkLodNoCountTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    s32 wait = _68 == _6c ? _68 : sead::GlobalRandom::instance()->getS32Range(_68, _6c);
    _60 = wait;
    if (_50 == 2)
        _50 = 0;
    if (wait < 0)
        setEndState();
}

void ForkLodNoCountTimer::leave_() {
    Fork::leave_();
}

void ForkLodNoCountTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
    getStaticParam(&mCamDist_s, "CamDist");
    getStaticParam(&mIsTrgStart_s, "IsTrgStart");
}

void ForkLodNoCountTimer::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
