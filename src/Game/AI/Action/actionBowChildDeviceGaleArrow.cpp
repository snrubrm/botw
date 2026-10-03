#include "Game/AI/Action/actionBowChildDeviceGaleArrow.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

BowChildDeviceGaleArrow::BowChildDeviceGaleArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceGaleArrow::~BowChildDeviceGaleArrow() = default;

bool BowChildDeviceGaleArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceGaleArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: store pairing (the original pairs _6c/_70 and stores _74 on its own; ours pairs _70/_74)
    const f32 angle = static_cast<f32>(*mID_d) * sead::Mathf::piHalf();
    _74 = 0.0f;
    _6c = 0.0f;
    _70 = 0.1f;
    _60 = 0;
    _64 = false;
    _68 = angle;
}

void BowChildDeviceGaleArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildDeviceGaleArrow::loadParams_() {
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mRotateSpeedMax_s, "RotateSpeedMax");
    getStaticParam(&mRotateAccel_s, "RotateAccel");
    getStaticParam(&mRotateOffset_s, "RotateOffset");
    getStaticParam(&mCenterOffset_s, "CenterOffset");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildDeviceGaleArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
