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
    _50._0 = !*mIsTrgStart_s;
    const int wait = *mWaitFrame_s;
    const int wait_max = *mWaitFrameRand_s + wait;
    _50._18 = sead::Mathi::min(wait, wait_max);
    _50._1c = sead::Mathi::max(wait, wait_max);
    _50._14 = *mCamDist_s;
    return true;
}

void ForkLodNoCountTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    s32 wait = _50._18 == _50._1c ? _50._18 : sead::GlobalRandom::instance()->getS32Range(_50._18, _50._1c);
    _50._10 = wait;
    if (_50._0 == 2)
        _50._0 = 0;
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
    if (_50._10 < 0.0f)
        setEndState();
    else
        _50.sub_7100709414();
}

}  // namespace uking::action
