#include "Game/AI/AI/aiSafeMoveAroundTarget.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

SafeMoveAroundTarget::SafeMoveAroundTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SafeMoveAroundTarget::~SafeMoveAroundTarget() = default;

bool SafeMoveAroundTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SafeMoveAroundTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: timer stores and random endpoint conversions are scheduled differently.
    _b0.reset(*mStartRange_s, *mChangeRangeRate_s);
    _bc.reset(-1.0f);
    _c8.reset(-1.0f);
    _d4.reset(-1.0f);
    const s32 base = *mForceTurnTimeBase_s;
    const s32 end = base + *mForceTurnTimeRand_s;
    _c8.value = _c8.previous_value =
        sead::GlobalRandom::instance()->getF32Range(f32(base), f32(end));
    sub_71005553EC();
}

void SafeMoveAroundTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SafeMoveAroundTarget::loadParams_() {
    getStaticParam(&mForceTurnTimeBase_s, "ForceTurnTimeBase");
    getStaticParam(&mForceTurnTimeRand_s, "ForceTurnTimeRand");
    getStaticParam(&mForceTurnStopTimeBase_s, "ForceTurnStopTimeBase");
    getStaticParam(&mForceTurnStopTimeRand_s, "ForceTurnStopTimeRand");
    getStaticParam(&mUpdateTargetPosTime_s, "UpdateTargetPosTime");
    getStaticParam(&mUpdateNumCalc_s, "UpdateNumCalc");
    getStaticParam(&mStartRange_s, "StartRange");
    getStaticParam(&mEndRange_s, "EndRange");
    getStaticParam(&mChangeRangeRate_s, "ChangeRangeRate");
    getStaticParam(&mTargetOffsetDegree_s, "TargetOffsetDegree");
    getStaticParam(&mLOSFailOffsetDegree_s, "LOSFailOffsetDegree");
    getStaticParam(&mMinOffsetLength_s, "MinOffsetLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
