#include "Game/AI/AI/aiSafeMoveAroundTarget.h"
#include <math/seadMathCalcCommon.h>
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

// NON_MATCHING: random endpoint conversions and timer/vector stores are scheduled differently.
void SafeMoveAroundTarget::calc_() {
    if (isFinished() || isFailed())
        return;
    _bc.update();
    if (!(_c8.value <= sead::Mathf::epsilon())) {
        _c8.update();
        if (_c8.value <= sead::Mathf::epsilon()) {
            const s32 base = *mForceTurnStopTimeBase_s;
            const s32 end = base + *mForceTurnStopTimeRand_s;
            _d4.value = _d4.previous_value =
                sead::GlobalRandom::instance()->getF32Range(f32(base), f32(end));
        }
    }
    if (!(_d4.value <= sead::Mathf::epsilon())) {
        _d4.update();
        if (_d4.value <= sead::Mathf::epsilon()) {
            const s32 base = *mForceTurnTimeBase_s;
            const s32 end = base + *mForceTurnTimeRand_s;
            _c8.value = _c8.previous_value =
                sead::GlobalRandom::instance()->getF32Range(f32(base), f32(end));
        }
    }
    if (_b0.value > *mEndRange_s * 0.95f)
        _b0.update();
    if (_bc.value <= sead::Mathf::epsilon()) {
        _a4 = sub_71005556F0();
        if (_a4.x == 0.0f && _a4.y == 0.0f && _a4.z == 0.0f) {
            setFailed();
            return;
        }
        getCurrentChild()->setDynamicParam(_a4, "TargetPos");
        _bc.value = _bc.previous_value = f32(*mUpdateTargetPosTime_s);
    }
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
