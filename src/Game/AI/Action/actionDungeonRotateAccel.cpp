#include "Game/AI/Action/actionDungeonRotateAccel.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

DungeonRotateAccel::DungeonRotateAccel(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateAccel::~DungeonRotateAccel() = default;

bool DungeonRotateAccel::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateAccel::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    m34(*mDynAngAccel_d);
    mFlags.set(Flag::Changeable);
}

void DungeonRotateAccel::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateAccel::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mIsSlowDown_s, "IsSlowDown");
    getDynamicParam(&mDynCurrentAngVel_d, "DynCurrentAngVel");
    getDynamicParam(&mDynAngAccel_d, "DynAngAccel");
}

void DungeonRotateAccel::calc_() {
    DungeonRotateBase::calc_();
}

void DungeonRotateAccel::m33() {
    _84 = *mDynCurrentAngVel_d;
}

float DungeonRotateAccel::m32() {
    f32 speed;
    if (*mIsSlowDown_s)
        speed = 0.0f;
    else
        speed = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    _88 = speed;
    return speed;
}

}  // namespace uking::action
