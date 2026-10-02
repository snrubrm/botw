#include "Game/AI/Action/actionForkAddCalcScaleMapUnit.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAddCalcScaleMapUnit::ForkAddCalcScaleMapUnit(const InitArg& arg) : Fork(arg) {}

ForkAddCalcScaleMapUnit::~ForkAddCalcScaleMapUnit() = default;

bool ForkAddCalcScaleMapUnit::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkAddCalcScaleMapUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _58 = mActor->getScale().x;
    _54 = _58 / *mScaleTime_m;
    _50 = sead::Mathf::clamp(_58 * *mMinAddScaleRate_s, 0.0f, 1.0f);
    f32 scale = *mStartRate_s * _58;
    if (scale <= 0.0f) {
        scale = 0.0f;
        ksys::VFR::lerp(&scale, _58, *mAddRate_s, _54, _50);
    }
    mActor->setScale({scale, scale, scale});
}

void ForkAddCalcScaleMapUnit::leave_() {
    Fork::leave_();
}

void ForkAddCalcScaleMapUnit::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mStartRate_s, "StartRate");
    getStaticParam(&mAddRate_s, "AddRate");
    getStaticParam(&mMinAddScaleRate_s, "MinAddScaleRate");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
}

void ForkAddCalcScaleMapUnit::calc_() {
    Fork::calc_();
    f32 scale = mActor->getScale().x;
    if (scale == _58) {
        setEndState();
        return;
    }
    ksys::VFR::lerp(&scale, _58, *mAddRate_s, _54, _50);
    mActor->setScale({scale, scale, scale});
}

}  // namespace uking::action
