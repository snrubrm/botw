#include "Game/AI/Action/actionHover.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

Hover::Hover(const InitArg& arg) : HoverBase(arg) {}

Hover::~Hover() = default;

bool Hover::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void Hover::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
    const f32 time = *mTime_s + *mTimeRand_s * sead::GlobalRandom::instance()->getF32();
    _60 = ksys::Timer(time, time);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void Hover::leave_() {
    HoverBase::leave_();
}

void Hover::loadParams_() {
    HoverBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mASName_s, "ASName");
}

void Hover::calc_() {
    HoverBase::calc_();
    if (*mTime_s <= 0)
        return;
    if (_60.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }
    _60.update();
}

}  // namespace uking::action
