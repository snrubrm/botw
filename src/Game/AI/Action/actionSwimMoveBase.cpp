#include "Game/AI/Action/actionSwimMoveBase.h"

namespace uking::action {

// NON_MATCHING: order of the zeroing stores for the params
SwimMoveBase::SwimMoveBase(const InitArg& arg) : WaterFloatBase(arg) {}

bool SwimMoveBase::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void SwimMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void SwimMoveBase::leave_() {
    WaterFloatBase::leave_();
}

void SwimMoveBase::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void SwimMoveBase::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
