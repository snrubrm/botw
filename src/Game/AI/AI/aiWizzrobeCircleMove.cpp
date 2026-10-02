#include "Game/AI/AI/aiWizzrobeCircleMove.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

WizzrobeCircleMove::WizzrobeCircleMove(const InitArg& arg) : CircleMoveTarget(arg) {}

WizzrobeCircleMove::~WizzrobeCircleMove() = default;

bool WizzrobeCircleMove::init_(sead::Heap* heap) {
    return CircleMoveTarget::init_(heap);
}

void WizzrobeCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mRadiusTimer_s > 0.0f) {
        _8c = ksys::Timer(*mRadiusTimer_s, *mRadiusTimer_s);
        _88 = false;
    } else {
        _88 = true;
        if (*mEndTimer_s > 0.0f) {
            _8c = ksys::Timer(*mEndTimer_s, *mEndTimer_s);
        } else {
            _8c = ksys::Timer();
            setFinished();
        }
    }
    CircleMoveTarget::enter_(params);
}

void WizzrobeCircleMove::calc_() {
    CircleMoveTarget::calc_();
    if (_88) {
        if (!(_8c.value <= sead::Mathf::epsilon()))
            _8c.update();
        if (!(_8c.value <= sead::Mathf::epsilon()))
            return;
    } else {
        _8c.update();
        if (!(_8c.value <= sead::Mathf::epsilon()))
            return;
        _88 = true;
        if (*mEndTimer_s > 0.0f) {
            _8c = ksys::Timer(*mEndTimer_s, *mEndTimer_s);
            return;
        }
        _8c = ksys::Timer();
    }
    if (getCurrentChild()->isChangeable())
        setFinished();
}

void WizzrobeCircleMove::leave_() {
    CircleMoveTarget::leave_();
}

void WizzrobeCircleMove::loadParams_() {
    CircleMoveTarget::loadParams_();
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mRadiusTimer_s, "RadiusTimer");
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mIsAttCentral_s, "IsAttCentral");
}

}  // namespace uking::ai
