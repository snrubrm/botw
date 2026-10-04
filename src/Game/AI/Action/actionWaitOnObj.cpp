#include "Game/AI/Action/actionWaitOnObj.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

WaitOnObj::WaitOnObj(const InitArg& arg) : WaitOnObjBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WaitOnObj::~WaitOnObj() {
    ;
}

bool WaitOnObj::init_(sead::Heap* heap) {
    return WaitOnObjBase::init_(heap);
}

void WaitOnObj::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitOnObjBase::enter_(params);
    const f32 time = *mTime_s + *mTimeRand_s * sead::GlobalRandom::instance()->getF32();
    _d8 = ksys::Timer(time, time);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void WaitOnObj::leave_() {
    WaitOnObjBase::leave_();
}

void WaitOnObj::loadParams_() {
    WaitOnObjBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mASName_s, "ASName");
}

void WaitOnObj::calc_() {
    WaitOnObjBase::calc_();
    if (*mTime_s <= 0)
        return;
    if (_d8.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }
    _d8.update();
}

}  // namespace uking::action
